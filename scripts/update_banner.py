import os, re, requests, sys

# ================================================================
# 🧭 Repository Configuration
# ================================================================
OWNER = "r3c-foundation"
REPO = "r3c"
README_PATH = "README.md"

# ================================================================
# 🔐 Auth Header (GH_TOKEN)
# ================================================================
token = os.getenv("GH_TOKEN")
if not token:
    print("❌ Error: GH_TOKEN not found in environment.")
    sys.exit(1)

headers = {"Authorization": f"Bearer {token}"}

# ================================================================
# 📊 Fetch Repository Info
# ================================================================
print("📡 Fetching repository statistics...")

repo_info = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}", headers=headers).json()
stars = repo_info.get("stargazers_count", 0)

tags = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}/tags", headers=headers).json()
version = tags[0]["name"] if tags else "v0.0.0"

clones_data = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}/traffic/clones", headers=headers).json()
views_data = requests.get(f"https://api.github.com/repos/{OWNER}/{REPO}/traffic/views", headers=headers).json()

clones = clones_data.get("count", 0)
unique_cloners = clones_data.get("uniques", 0)
views = views_data.get("count", 0)
visitors = views_data.get("uniques", 0)

print(f"""
⭐ Stars: {stars}
🔖 Version: {version}
🧭 Clones: {clones}
👥 Unique Cloners: {unique_cloners}
📈 Views: {views}
👁 Unique Visitors: {visitors}
""")

# ================================================================
# 🧩 Banner Block Template
# ================================================================
new_banner = f"""<!-- AUTO-BANNER:START -->
🌸 **R3C — Rust Independence Compiler**  
Rewrite the base. Build compilers that heal themselves.  
Cross-platform C++ · NASM · Rust transpiler pipeline  

| Stars | Version | Clones (14d) | Unique Cloners | Views (14d) | Visitors (14d) | License |
|:------|:--------|:-------------|:----------------|:-------------|:----------------|:---------|
| ⭐ {stars} | 🔖 {version} | 🧭 {clones} | 👥 {unique_cloners} | 📈 {views} | 👁 {visitors} | ⚖️ MIT |
<!-- AUTO-BANNER:END -->
"""

# ================================================================
# ✏️ Update README.md
# ================================================================
if not os.path.exists(README_PATH):
    print(f"❌ README.md not found at path: {README_PATH}")
    sys.exit(1)

with open(README_PATH, "r", encoding="utf-8") as f:
    content = f.read()

if "<!-- AUTO-BANNER:START -->" in content:
    content = re.sub(
        r"<!-- AUTO-BANNER:START -->.*<!-- AUTO-BANNER:END -->",
        new_banner,
        content,
        flags=re.DOTALL
    )
    print("🔁 Existing banner updated.")
else:
    content = new_banner + "\n\n" + content
    print("🆕 Banner block added to README.")

with open(README_PATH, "w", encoding="utf-8") as f:
    f.write(content)

print("✅ README banner updated successfully!")
