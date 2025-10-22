import os, json, datetime, requests, matplotlib.pyplot as plt

repos = [
    "0200134/r3c",
    "0200134/cpppm",
    "0200134/Rust-ltss"
]

token = os.environ["GITHUB_TOKEN"]
headers = {"Authorization": f"token {token}"}

def get_json(repo, endpoint):
    r = requests.get(f"https://api.github.com/repos/{repo}/traffic/{endpoint}", headers=headers)
    if r.status_code == 200:
        return r.json()
    else:
        print(f"⚠️ Failed to fetch {endpoint} for {repo}: {r.status_code}")
        return {"count":0,"uniques":0,"views":[],"clones":[]}

today = datetime.date.today().isoformat()
os.makedirs("traffic/data", exist_ok=True)
summary = {"date": today, "repos": {}}

total_views = total_uniques = total_clones = total_cloners = 0

for repo in repos:
    views = get_json(repo, "views")
    clones = get_json(repo, "clones")
    referrers = requests.get(f"https://api.github.com/repos/{repo}/traffic/popular/referrers", headers=headers).json()
    summary["repos"][repo] = {"views": views, "clones": clones, "referrers": referrers}

    total_views += views.get("count", 0)
    total_uniques += views.get("uniques", 0)
    total_clones += clones.get("count", 0)
    total_cloners += clones.get("uniques", 0)

with open(f"traffic/data/{today}.json", "w") as f:
    json.dump(summary, f, indent=2)

# --- 그래프 생성 ---
plt.figure(figsize=(8,4))
for repo in repos:
    v = summary["repos"][repo]["views"].get("views", [])
    if not v:
        continue
    days = [d["timestamp"][:10] for d in v]
    counts = [d["count"] for d in v]
    plt.plot(days, counts, marker='o', label=repo.split('/')[-1])

plt.title("Combined GitHub Views (Last 14 Days)")
plt.xticks(rotation=45)
plt.legend()
plt.tight_layout()
plt.savefig("traffic/summary.png")

# --- README 업데이트 ---
section = f"""
<!--TRAFFIC_START-->
## 📊 Combined GitHub Traffic (last 14 days)

![Traffic Chart](traffic/summary.png)

| Metric | Total | Unique |
|--------|--------|--------|
| **Views** | {total_views} | {total_uniques} |
| **Clones** | {total_clones} | {total_cloners} |

**Repositories Monitored:**  
- r3c  
- cpppm  
- Rust-ltss
"""

with open("README.md", "r", encoding="utf-8") as f:
    content = f.read()

if "<!--TRAFFIC_START-->" in content:
    content = content.split("<!--TRAFFIC_START-->")[0] + section
else:
    content += "\n" + section

with open("README.md", "w", encoding="utf-8") as f:
    f.write(content)
