import os, requests, matplotlib.pyplot as plt
from datetime import datetime

# 트래픽을 모니터링할 리포 목록
REPOS = ["0200134/r3c", "0200134/cpppm", "0200134/Rust-ltss"]
TOKEN = os.getenv("GITHUB_TOKEN")
HEADERS = {"Authorization": f"token {TOKEN}"}

def fetch_traffic(repo):
    url = f"https://api.github.com/repos/{repo}/traffic/views"
    res = requests.get(url, headers=HEADERS)
    if res.status_code != 200:
        print(f"❌ Failed: {repo} ({res.status_code})")
        return None
    return res.json()

def plot_combined(data):
    plt.figure(figsize=(10, 6))
    for repo, stats in data.items():
        if not stats: continue
        dates = [v["timestamp"][:10] for v in stats["views"]]
        counts = [v["count"] for v in stats["views"]]
        plt.plot(dates, counts, marker="o", label=repo)
    plt.title("📊 Combined GitHub Traffic (Views per Day)")
    plt.xlabel("Date")
    plt.ylabel("Views")
    plt.legend()
    plt.xticks(rotation=45)
    plt.tight_layout()
    os.makedirs("traffic", exist_ok=True)
    plt.savefig("traffic/combined_traffic.png")
    plt.close()
    print("✅ Graph saved: traffic/combined_traffic.png")

def update_readme():
    with open("README.md", "r", encoding="utf-8") as f:
        lines = f.readlines()
    marker = "## 📊 Combined GitHub Traffic"
    new_block = (
        f"{marker}\n"
        f"![Traffic](./traffic/combined_traffic.png)\n\n"
        f"> *Last updated: {datetime.utcnow().strftime('%Y-%m-%d %H:%M UTC')}*"
    )
    with open("README.md", "w", encoding="utf-8") as f:
        found = False
        for line in lines:
            if line.strip().startswith(marker):
                f.write(new_block + "\n")
                found = True
                break
            f.write(line)
        if not found:
            f.write("\n" + new_block + "\n")
    print("✅ README updated with traffic graph")

if __name__ == "__main__":
    results = {}
    for repo in REPOS:
        print(f"📡 Fetching traffic for {repo}...")
        results[repo] = fetch_traffic(repo)
    plot_combined(results)
    update_readme()
