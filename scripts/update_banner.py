import os, re, requests

# -------------------------------
# 🔧 기본 설정
# -------------------------------
OWNER = "r3c-foundation"
REPO = "r3c"
README_PATH = "README.md"

# GitHub API 인증
headers = {"Authorization": f"Bearer {os.getenv('GH_TOKEN')}"}

# -------------------------------
# 📊 리포지토리 정보 가져오기
# -------------------------------
repo_info = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}", headers=headers).json()
stars = repo_info.get("stargazers_count", 0)

# 최신 태그 (버전)
tags = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}/tags", headers=headers).json()
version = tags[0]["name"] if tags else "v0.0.0"

# -------------------------------
# 👁️ 트래픽 통계 (Views + Clones)
# -------------------------------
clones_data = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}/traffic/clones", headers=headers).json()
views_data = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}/traffic/views", headers=headers).json()

clones = clones_data.get("count", 0)
unique_cloners = clones_data.get("uniques", 0)
views = views_data.get("count", 0)
visitors = views_data.get("uniques", 0)

# -------------------------------
# 🧩 새 배너 블록 생성
# -------------------------------
new_banner = f"""<!-- AUTO-BANNER:START -->
🌸 **R3C — Rust Independence Compiler**  
Rewrite the base. Build compilers that heal themselves.  
Cross-platform C++ · NASM · Rust transpiler pipeline  

| Stars | Version | Clones (14d) | Unique Cloners | Views (14d) | Visitors (14d) | License |
|:------|:--------|:-------------|:----------------|:-------------|:----------------|:---------|
| ⭐ {stars} | 🔖 {version} | 🧭 {clones} | 👥 {unique_cloners} | 📈 {views} | 👁 {visitors} | ⚖️ MIT |
<!-- AUTO-BANNER:END -->"""

# -------------------------------
# ✏️ README.md 업데이트
# -------------------------------
with open(README_PATH, "r", encoding="utf-8") as f:
    content = f.read()

if "<!-- AUTO-BANNER:START -->" in content:
    content = re.sub(
        r"<!-- AUTO-BANNER:START -->.*<!-- AUTO-BANNER:END -->",
        new_banner,
        content,
        flags=re.DOTALL
    )
else:
    content = new_banner + "\n\n" + content

with open(README_PATH, "w", encoding="utf-8") as f:
    f.write(content)

print("✅ README banner updated successfully!")
print(f"Stars: {stars}, Clones: {clones}, Unique Cloners: {unique_cloners}, Views: {views}, Visitors: {visitors}, Version: {version}")
