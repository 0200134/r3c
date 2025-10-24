import requests, os, datetime, matplotlib.pyplot as plt

repo = os.getenv("GITHUB_REPOSITORY", "r3c-foundation/r3c")
token = os.getenv("GH_TOKEN")

headers = {"Authorization": f"token {token}"}
views_url = f"https://api.github.com/repos/{repo}/traffic/views"
clones_url = f"https://api.github.com/repos/{repo}/traffic/clones"
info_url = f"https://api.github.com/repos/{repo}"

views = requests.get(views_url, headers=headers).json()
clones = requests.get(clones_url, headers=headers).json()
info = requests.get(info_url, headers=headers).json()

total_views = views.get("count", 0)
unique_visitors = views.get("uniques", 0)
total_clones = clones.get("count", 0)
unique_cloners = clones.get("uniques", 0)
stars = info.get("stargazers_count", 0)
license_name = info.get("license", {}).get("spdx_id", "MIT")

# === 그래프 생성 ===
try:
    days = [v["timestamp"][:10] for v in views["views"]]
    counts = [v["count"] for v in views["views"]]
    plt.figure(figsize=(6,3))
    plt.plot(days, counts, marker="o")
    plt.title("R3C Traffic (Last 14 days)")
    plt.xlabel("Date")
    plt.ylabel("Views")
    plt.grid(True, alpha=0.3)
    plt.xticks(rotation=45, ha="right")
    plt.tight_layout()
    plt.savefig("traffic_graph.png", dpi=120)
    print("✅ traffic_graph.png generated.")
except Exception as e:
    print("⚠️ Graph generation skipped:", e)

# === 배너 텍스트 ===
banner = f"""🌸 R3C — Rust Independence Compiler  
Rewrite the base. Build compilers that heal themselves.  
Cross-platform C++ · NASM · Rust transpiler pipeline

⭐ Stars: {stars} 👁 Views(14d): {total_views} 🧭 Clones(14d): {total_clones}  
⚖️ License: {license_name} 🕒 Updated: {datetime.datetime.utcnow().strftime("%Y-%m-%d %H:%M UTC")}
"""

# === README 삽입 ===
try:
    with open("README.md", "r", encoding="utf-8") as f:
        lines = f.readlines()
except FileNotFoundError:
    lines = []

start, end = None, None
for i, line in enumerate(lines):
    if "<!--AUTO-BANNER-START-->" in line:
        start = i
    if "<!--AUTO-BANNER-END-->" in line:
        end = i

banner_block = f"<!--AUTO-BANNER-START-->\n{banner}\n![Traffic Graph](traffic_graph.png)\n<!--AUTO-BANNER-END-->\n"

if start is not None and end is not None:
    lines[start:end+1] = [banner_block]
else:
    lines.insert(0, banner_block + "\n")

with open("README.md", "w", encoding="utf-8") as f:
    f.writelines(lines)

print("✅ README updated with traffic banner + graph.")
