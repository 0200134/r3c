import os, requests, datetime
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

REPO = os.getenv("GITHUB_REPOSITORY", "r3c-foundation/r3c")
TOKEN = os.getenv("GH_TOKEN") or os.getenv("GITHUB_TOKEN")
HEADERS = {"Authorization": f"token {TOKEN}"} if TOKEN else {}
README_PATH = "README.md"
GRAPH_PATH = "traffic_graph.png"

def fetch_traffic():
    base = f"https://api.github.com/repos/{REPO}/traffic"
    v = requests.get(f"{base}/views", headers=HEADERS).json()
    c = requests.get(f"{base}/clones", headers=HEADERS).json()
    return {
        "views": v.get("count", 0),
        "clones": c.get("count", 0),
        "unique_views": v.get("uniques", 0),
        "unique_clones": c.get("uniques", 0),
        "views_daily": v.get("views", []),
        "clones_daily": c.get("clones", []),
        "today_views": v.get("views", [])[-1]["uniques"] if v.get("views") else 0,
        "today_clones": c.get("clones", [])[-1]["uniques"] if c.get("clones") else 0,
    }

def make_graph(d):
    plt.figure(figsize=(6,3))
    plt.plot([v["count"] for v in d["views_daily"]], label="Views", linewidth=2)
    plt.plot([c["count"] for c in d["clones_daily"]], label="Clones", linewidth=2)
    plt.title("GitHub Traffic (Last 14 days)")
    plt.legend()
    plt.tight_layout()
    plt.savefig(GRAPH_PATH, dpi=200)
    plt.close()
    print("✅ traffic_graph.png generated.")

def update_readme(d):
    today_line = f"📊 Today: {d['today_views']} visitors, {d['today_clones']} cloners ({datetime.datetime.utcnow().strftime('%Y-%m-%d %H:%M UTC')})"
    with open(README_PATH, "r", encoding="utf-8") as f:
        txt = f.read()

    # 그래프 한 번만 유지
    txt = "\n".join([l for l in txt.splitlines() if "traffic_graph.png" not in l])
    txt += f"\n\n![Traffic Graph]({GRAPH_PATH})\n"

    # 일일 로그 추가/유지
    if "## 📈 Daily Traffic Log" in txt:
        head, log = txt.split("## 📈 Daily Traffic Log", 1)
        lines = [l.strip() for l in log.splitlines() if l.strip()]
        if today_line not in lines: lines.append(today_line)
        lines = lines[-30:]  # 최근 30일만 유지
        txt = f"{head}## 📈 Daily Traffic Log\n\n" + "\n".join(lines) + "\n"
    else:
        txt += f"\n## 📈 Daily Traffic Log\n\n{today_line}\n"

    with open(README_PATH, "w", encoding="utf-8") as f:
        f.write(txt)
    print(f"✅ README updated with {today_line}")

if __name__ == "__main__":
    print("📡 Fetching GitHub traffic data...")
    data = fetch_traffic()
    print(f"👁 {data['today_views']} visitors / 🧭 {data['today_clones']} cloners today")
    make_graph(data)
    update_readme(data)
    print("🎉 Graph + Daily Log updated successfully!")
