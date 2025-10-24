import os, re, requests

OWNER = "r3c-foundation"
REPO = "r3c"
README_PATH = "README.md"
headers = {"Authorization": f"Bearer {os.getenv('GH_TOKEN')}"}

# 🌟 Stars
repo_info = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}", headers=headers).json()
stars = repo_info.get("stargazers_count", 0)

# 🔖 Latest tag
tags = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}/tags", headers=headers).json()
version = tags[0]["name"] if tags else "v0.0.0"

# 🧭 Clones & Visitors
clones = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}/traffic/clones", headers=headers).json()
views = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}/traffic/views", headers=headers).json()

clone_count = clones.get("count", 0)
visitors = views.get("uniques", 0)

# 🔄 새 블록 생성
new_banner = f"""<!-- AUTO-BANNER:START -->
🌸 **R3C — Rust Independence Compiler**  
Rewrite the base. Build compilers that heal themselves.  
Cross-platform C++ · NASM · Rust transpiler pipeline  

| Stars | Version | Clones (14d) | Visitors (14d) | License |
|:------|:--------|:-------------|:----------------|:---------|
| ⭐ {stars} | 🔖 {version} | 🧭 {clone_count} | 👁 {visitors} | ⚖️ MIT |
<!-- AUTO-BANNER:END -->"""

# ✏️ README 수정
with open(README_PATH, "r", encoding="utf-8") as f:
    content = f.read()

content = re.sub(r"<!-- AUTO-BANNER:START -->.*<!-- AUTO-BANNER:END -->", new_banner, content, flags=re.DOTALL)

with open(README_PATH, "w", encoding="utf-8") as f:
    f.write(content)

print("✅ README banner updated.")
