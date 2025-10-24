import requests, re, os

OWNER = "r3c-foundation"
REPO = "r3c"
README_PATH = "README.md"

# GitHub API 인증
headers = {"Authorization": f"Bearer {os.getenv('GH_TOKEN')}"}

# 1️⃣ 스타 수 가져오기
stars = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}", headers=headers).json()["stargazers_count"]

# 2️⃣ 트래픽 통계
traffic = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}/traffic/views", headers=headers).json()
visitors = traffic.get("uniques", 0)
clones = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}/traffic/clones", headers=headers).json().get("count", 0)

# 3️⃣ 버전 정보 (태그 최신)
tags = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}/tags", headers=headers).json()
version = tags[0]["name"] if tags else "v0.0.0"

# 4️⃣ README 갱신
with open(README_PATH, "r", encoding="utf-8") as f:
    content = f.read()

new_banner = f"""<!-- AUTO-BANNER:START -->
🌸 **R3C — Rust Independence Compiler**  
Rewrite the base. Build compilers that heal themselves.  
Cross-platform C++ · NASM · Rust transpiler pipeline  

| Stars | Version | Clones (14d) | Visitors (14d) | License |
|:------|:--------|:-------------|:----------------|:---------|
| ⭐ {stars} | 🔖 {version} | 🧭 {clones} | 👁 {visitors} | ⚖️ MIT |
<!-- AUTO-BANNER:END -->"""

content = re.sub(r"<!-- AUTO-BANNER:START -->.*<!-- AUTO-BANNER:END -->", new_banner, content, flags=re.DOTALL)

with open(README_PATH, "w", encoding="utf-8") as f:
    f.write(content)
