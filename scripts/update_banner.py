import os
import requests
import datetime
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import re

# ================================================================
# 🔧 Environment & Constants
# ================================================================
REPO = os.getenv("GITHUB_REPOSITORY", "r3c-foundation/r3c")
TOKEN = os.getenv("GH_TOKEN") or os.getenv("GITHUB_TOKEN")
HEADERS = {"Authorization": f"token {TOKEN}"} if TOKEN else {}

README_PATH = "README.md"
GRAPH_PATH = "traffic_graph.png"

# ================================================================
# 📊 Fetch GitHub Traffic Data
# ================================================================
def fetch_traffic():
    views_url = f"https://api.github.com/repos/{REPO}/traffic/views"
    clones_url = f"https://api.github.com/repos/{REPO}/traffic/clones"

    views_data = requests.get(views_url, headers=HEADERS).json()
    clones_data = requests.get(clones_url, headers=HEADERS).json()

    views_count = views_data.get("count", 0)
    views_uniques = views_data.get("uniques", 0)
    clones_count = clones_data.get("count", 0)
    clones_uniques = clones_data.get("uniques", 0)

    views_daily = views_data.get("views", [])
    clones_daily = clones_data.get("clones", [])

    return {
        "views": views_count,
        "unique_views": views_uniques,
        "clones": clones_count,
        "unique_clones": clones_uniques,
        "views_daily": views_daily,
        "clones_daily": clones_daily,
    }

# ================================================================
# 📈 Generate Traffic Graph
# ================================================================
def make_graph(data):
    plt.figure(figsize=(6, 3))
    plt.plot([v["count"] for v in data["views_daily"]], label="Views", linewidth=2)
    plt.plot([c["count"] for c in data["clones_daily"]], label="Clones", linewidth=2)
    plt.title("GitHub Traffic (Last 14 days)")
    plt.legend()
    plt.tight_layout()
    plt.savefig(GRAPH_PATH)
    plt.close()

# ================================================================
# 🪄 Update README Banner Section (No duplication)
# ================================================================
def update_readme(data):
    if not os.path.exists(README_PATH):
        print("❌ README.md not found")
        return

    now = datetime.datetime.utcnow().strftime("%Y-%m-%d %H:%M UTC")

    banner = (
        f"🌸 R3C — Rust Independence Compiler\n"
        f"Rewrite the base. Build compilers that heal themselves.\n"
        f"Cross-platform C++ · NASM · Rust transpiler pipeline\n\n"
        f"⭐ Stars: 1 👁️ Views(14d): {data['views']} ⏱️ Clones(14d): {data['clones']}\n"
        f"🧑‍💻 Unique Visitors: {data['unique_views']} ↩️ Unique Cloners: {data['unique_clones']}\n"
        f"⚖️ License: MIT 🕒 Updated: {now}\n\n"
        f"![Traffic Graph]({GRAPH_PATH})\n"
    )

    with open(README_PATH, "r", encoding="utf-8") as f:
        content = f.read()

    # 🌸 R3C ~ ![Traffic Graph] 구간만 교체
    new_content = re.sub(
        r"🌸 R3C[\s\S]*?!\[Traffic Graph\]\(.*?\)\n?",
        banner,
        content,
        count=1
    )

    # 기존 배너가 없으면 상단에 삽입
    if new_content == content:
        new_content = banner + "\n" + content

    with open(README_PATH, "w", encoding="utf-8") as f:
        f.write(new_content)

    print("✅ README updated successfully (clean replacement).")

# ================================================================
# 🚀 Main
# ================================================================
if __name__ == "__main__":
    print("📡 Fetching GitHub traffic data...")
    data = fetch_traffic()
    print(f"✅ Views: {data['views']}, Clones: {data['clones']}")
    make_graph(data)
    update_readme(data)
    print("🎉 README banner and traffic graph updated (clean).")
