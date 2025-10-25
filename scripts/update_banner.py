#!/usr/bin/env python3
import os
import re
import requests
import datetime
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# ================================================================
# 🔧 Environment & Constants
# ================================================================
REPO = os.getenv("GITHUB_REPOSITORY", "r3c-foundation/r3c")
TOKEN = os.getenv("GH_TOKEN") or os.getenv("GITHUB_TOKEN")
HEADERS = {"Authorization": f"token {TOKEN}"} if TOKEN else {}

README_PATH = "README.md"
GRAPH_PATH = "traffic_graph.png"
FONT_FAMILY = "DejaVu Sans"

# ================================================================
# 🧠 Utility Functions
# ================================================================
def safe_get(url):
    try:
        r = requests.get(url, headers=HEADERS)
        if r.status_code == 200:
            return r.json()
        else:
            print(f"⚠️ GitHub API error {r.status_code}: {url}")
            return {}
    except Exception as e:
        print(f"❌ Request failed: {e}")
        return {}

# ================================================================
# 📊 Fetch GitHub Traffic + Repo Stats
# ================================================================
def fetch_traffic():
    views_data = safe_get(f"https://api.github.com/repos/{REPO}/traffic/views")
    clones_data = safe_get(f"https://api.github.com/repos/{REPO}/traffic/clones")
    repo_data = safe_get(f"https://api.github.com/repos/{REPO}")

    return {
        "stars": repo_data.get("stargazers_count", 0),
        "views": views_data.get("count", 0),
        "unique_views": views_data.get("uniques", 0),
        "clones": clones_data.get("count", 0),
        "unique_clones": clones_data.get("uniques", 0),
        "views_daily": views_data.get("views", []),
        "clones_daily": clones_data.get("clones", []),
    }

# ================================================================
# 📈 Generate Graph
# ================================================================
def make_graph(data):
    plt.rcParams["font.family"] = FONT_FAMILY
    plt.figure(figsize=(6, 3))
    plt.plot([v["count"] for v in data["views_daily"]], label="Views", linewidth=2)
    plt.plot([c["count"] for c in data["clones_daily"]], label="Clones", linewidth=2)
    plt.title("GitHub Traffic (Last 14 days)", fontsize=10)
    plt.legend()
    plt.tight_layout()
    plt.savefig(GRAPH_PATH)
    plt.close()
    print("✅ Traffic graph generated.")

# ================================================================
# 🪄 Update README Between Markers
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
        f"⭐ Stars: {data['stars']}   👁️ Views(14d): {data['views']}   "
        f"🧭 Clones(14d): {data['clones']}\n"
        f"🧑‍💻 Unique Visitors: {data['unique_views']}   "
        f"🔁 Unique Cloners: {data['unique_clones']}\n"
        f"⚖️ License: MIT   🕒 Updated: {now}\n\n"
        f"![Traffic Graph]({GRAPH_PATH})\n"
    )

    with open(README_PATH, "r", encoding="utf-8") as f:
        content = f.read()

    pattern = r"<!--AUTO-BANNER-START-->[\\s\\S]*<!--AUTO-BANNER-END-->"
    new_block = f"<!--AUTO-BANNER-START-->\n{banner}\n<!--AUTO-BANNER-END-->"

    if re.search(pattern, content):
        content = re.sub(pattern, new_block, content)
    else:
        # no marker found → insert at top
        content = new_block + "\n\n" + content

    with open(README_PATH, "w", encoding="utf-8") as f:
        f.write(content)

    print("✅ README updated successfully.")

# ================================================================
# 🚀 Main
# ================================================================
if __name__ == "__main__":
    print("📡 Fetching GitHub traffic and repo stats...")
    data = fetch_traffic()
    print(f"✅ Stars: {data['stars']}, Views: {data['views']}, Clones: {data['clones']}")
    make_graph(data)
    update_readme(data)
    print("🎉 README banner + traffic graph updated successfully!")
