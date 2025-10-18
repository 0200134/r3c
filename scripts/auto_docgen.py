import re, glob

def extract_signatures(src_dir):
    result = []
    for path in glob.glob(f"{src_dir}/**/*.cpp", recursive=True):
        with open(path, encoding="utf-8") as f:
            lines = f.readlines()
        result.append(f"## {path}\n")
        for line in lines:
            if re.match(r"^(?:[a-zA-Z_]\w*\s+)+[a-zA-Z_]\w*\s*\([^)]*\)\s*\{?", line.strip()):
                result.append(f"- `{line.strip()}`\n")
    return ''.join(result)

def main():
    output = "# 🔧 R3C Source Map (Auto-Generated)\n\n" + extract_signatures("src")
    with open("docs/R3C_Source_Map.md", "w", encoding="utf-8") as f:
        f.write(output)
    print("✅ R3C_Source_Map.md updated")

if __name__ == "__main__":
    main()
