import os
import re

def check_files():
    print("🔍 R3C Repository Auto Check\n")

    expected = [
        ".github/workflows/project-auto.yml",
        ".github/workflows/weekly-summary.yml",
        ".github/workflows/test-build.yml",
        "docs/R3C_Documentation.md",
        "README.md",
        "CMakeLists.txt",
    ]

    for f in expected:
        if os.path.exists(f):
            print(f"✅ Found: {f}")
        else:
            print(f"❌ Missing: {f}")

    print("\n🧾 Checking README for documentation links...")
    if os.path.exists("README.md"):
        with open("README.md", "r", encoding="utf-8") as fp:
            content = fp.read()
            links = ["docs/R3C_Documentation.md", "docs/R3C_Documentation.pdf"]
            for link in links:
                if link in content:
                    print(f"✅ Link OK: {link}")
                else:
                    print(f"⚠️ Missing link: {link}")

    print("\n⚙️ Checking GitHub Actions syntax...")
    wf_dir = ".github/workflows"
    if os.path.isdir(wf_dir):
        for wf in os.listdir(wf_dir):
            if wf.endswith(".yml"):
                with open(os.path.join(wf_dir, wf), "r", encoding="utf-8") as f:
                    text = f.read()
                    if "permissions:" in text and "projects:" in text:
                        print(f"❌ {wf}: 'projects:' key invalid → use 'issues:'/'pull-requests:' only")
                    else:
                        print(f"✅ {wf}: syntax looks valid")

    print("\n🚀 Done. Review above for missing automation files or invalid syntax.")

if __name__ == "__main__":
    check_files()
