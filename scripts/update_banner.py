import requests, os, json, datetime, matplotlib.pyplot as plt

repo = os.getenv("GITHUB_REPOSITORY", "r3c-foundation/r3c")
token = os.getenv("GH_TOKEN")

headers = {"Authorization": f"token {token}"}
stats_url = f"https://api.github.com/repos/{repo}/traffic/views"
clones_url = f"https://api.github.com/repos/{repo}/traffic/clones"
info_url = f"https://api.github.com/repos/{repo}"

views = requests.get(stats_url, headers=headers).json()
clones = requests.get(clones_url, headers=headers).json()
info = requests.get(info_url, headers=headers).json()

total_views = views.get("count", 0)
unique_visitors = views.get("uniques", 0)
total_clones = clones.get("count", 0)
unique_cloners = clones.get("uniques", 0)
stars = info.get("stargazers_count", 0)
license_name = info.get("license", {}).get("spdx_id", "MIT")

banner = f"""🌸 R3C — Rust Independence Compiler  
Rewrite the base. Build compilers that heal themselves.  
Cross-platform C++ · NASM · Rust transpiler pipeline

Stars: ⭐ {stars}  
Views (14d): 👁 {total_views} / {unique_visitors} unique  
Clones (14d): 🧭 {total_clones} / {unique_cloners} unique  
License: ⚖️ {license_name}  
Updated: {datetime.datetime.utcnow().strftime("%Y-%m-%d %H:%M UTC")}
"""

with open("README.md", "r", encoding="utf-8") as f:
    lines = f.readlines()

# Replace between banner markers if present
start, end = None, None
for i, line in enumerate(lines):
    if "<!--AUTO-BANNER-START-->" in line:
        start = i
    if "<!--AUTO-BANNER-END-->" in line:
        end = i

if start is not None and end is not None:
    lines[start+1:end] = [banner + "\n"]
else:
    lines.insert(0, "<!--AUTO-BANNER-START-->\n" + banner + "\n<!--AUTO-BANNER-END-->\n\n")

with open("README.md", "w", encoding="utf-8") as f:
    f.writelines(lines)

print("✅ README banner updated successfully.")
