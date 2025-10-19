import os, time, sys, json, pathlib
import requests
import pandas as pd
import matplotlib.pyplot as plt

OUT_DIR = pathlib.Path("analytics")
OUT_DIR.mkdir(parents=True, exist_ok=True)

CSV_PATH = OUT_DIR / "traffic_data.csv"
PNG_PATH = OUT_DIR / "traffic_chart.png"

REPO = os.environ["REPO"]  # e.g. "0200134/r3c"
TOKEN = os.environ["GITHUB_TOKEN"]

HEADERS = {
    "Authorization": f"token {TOKEN}",
    "Accept": "application/vnd.github+json",
    "X-GitHub-Api-Version": "2022-11-28",
}

SESSION = requests.Session()
SESSION.headers.update(HEADERS)

def req_with_retry(url, max_retry=5, backoff=2.0):
    for attempt in range(1, max_retry + 1):
        r = SESSION.get(url)
        # Traffic API can return 202 while generating stats
        if r.status_code == 202:
            time.sleep(backoff)
            backoff *= 1.6
            continue
        # Handle rate limit
        if r.status_code == 403 and r.headers.get("X-RateLimit-Remaining") == "0":
            reset = int(r.headers.get("X-RateLimit-Reset", "0"))
            wait = max(0, reset - int(time.time()) + 1)
            time.sleep(min(wait, 60))
            continue
        if r.ok:
            return r.json()
        # retry on transient 5xx
        if 500 <= r.status_code < 600:
            time.sleep(backoff)
            backoff *= 1.6
            continue
        r.raise_for_status()
    raise RuntimeError(f"Failed after retry: {url}")

def fetch_traffic():
    base = f"https://api.github.com/repos/{REPO}/traffic"
    views = req_with_retry(f"{base}/views")
    clones = req_with_retry(f"{base}/clones")
    vd = pd.DataFrame(views.get("views", []))
    cd = pd.DataFrame(clones.get("clones", []))
    # Normalize schema
    # views: timestamp,count,uniques
    # clones: timestamp,count,uniques
    vd["metric"] = "views"
    cd["metric"] = "clones"
    return vd, cd

def load_existing():
    if CSV_PATH.exists():
        try:
            df = pd.read_csv(CSV_PATH)
            # Ensure expected columns
            expected = {"timestamp","count","uniques","metric"}
            if not expected.issubset(df.columns):
                return pd.DataFrame(columns=list(expected))
            return df
        except Exception:
            return pd.DataFrame(columns=["timestamp","count","uniques","metric"])
    return pd.DataFrame(columns=["timestamp","count","uniques","metric"])

def merge_save(vd, cd):
    existing = load_existing()
    df = pd.concat([existing, vd, cd], ignore_index=True)
    # Drop dup by (timestamp, metric); keep latest
    df = df.drop_duplicates(subset=["timestamp","metric"], keep="last")
    # Sort by time
    df["timestamp"] = pd.to_datetime(df["timestamp"])
    df = df.sort_values(["timestamp","metric"]).reset_index(drop=True)
    df.to_csv(CSV_PATH, index=False)
    return df

def plot(df):
    if df.empty:
        print("⚠️ No data to plot.")
        return False
    piv = df.pivot_table(index="timestamp", columns="metric", values="count", aggfunc="last")
    plt.figure(figsize=(9,4.8))
    if "views" in piv:
        plt.plot(piv.index, piv["views"], marker="o", label="Views")
    if "clones" in piv:
        plt.plot(piv.index, piv["clones"], marker="s", label="Clones")
    plt.title("R3C GitHub Traffic (Views / Clones)")
    plt.xlabel("Date")
    plt.ylabel("Count")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(PNG_PATH)
    print(f"✅ Saved chart: {PNG_PATH}")
    return True

def main():
    vd, cd = fetch_traffic()
    if vd.empty and cd.empty:
        # still write empty CSV for structure
        merge_save(vd, cd)
        print("⚠️ GitHub returned empty traffic windows (try tomorrow).")
        sys.exit(0)
    df = merge_save(vd, cd)
    plotted = plot(df)
    if not plotted:
        sys.exit(0)

if __name__ == "__main__":
    main()
