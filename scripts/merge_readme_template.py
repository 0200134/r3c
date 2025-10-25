import os

README_PATH = "README.md"
TEMPLATE_PATH = "README.template.md"

if not os.path.exists(TEMPLATE_PATH):
    print("⚠️ README.template.md not found. Skipping merge.")
    exit(0)

with open(TEMPLATE_PATH, "r", encoding="utf-8") as f:
    template = f.read()

with open(README_PATH, "r", encoding="utf-8") as f:
    readme = f.read()

# Governance 영역 기준으로 병합
merged = template + "\n\n" + readme
with open(README_PATH, "w", encoding="utf-8") as f:
    f.write(merged)

print("✅ README template merged successfully.")
