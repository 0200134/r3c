import os
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

GRAPH_PATH = "traffic_graph.png"

# ================================================================
# 📊 Fetch GitHub Traffic Data
# ================================================================
def fetch_traffic():
    views_url = f"https://api.github.com/repos/{REPO}/traffic/views"
    clones_url = f"https://api.github.com/repos/{REPO}/traffic/clones"

    views_data = requests.get(views_url, headers=HEADERS).json()
    clones_data = requests.get(clones_url, headers=HEADERS).json()

    return {
        "views": views_data.get("count", 0),
        "unique_views": views_data.get("uniques", 0),
        "clones": clones_data.get("count", 0),
        "unique_clones": clones_data.get("uniques", 0),
        "views_daily": views_data.get("views", []),
        "clones_daily": clones_data.get("clones", []),
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
    plt.savefig(GRAPH_PATH, dpi=200)
    plt.close()
    print("✅ traffic_graph.png generated.")

# ================================================================
# 🚀 Main
# ================================================================
if __name__ == "__main__":
    print("📡 Fetching GitHub traffic data...")
    data = fetch_traffic()
    print(f"✅ Views: {data['views']}, Clones: {data['clones']}")
    make_graph(data)
    print("🎉 Graph updated successfully (README modification handled in workflow).")
