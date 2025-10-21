#!/usr/bin/env bash
set -e

# ============================================================
# 🧱 R3C Stub Generator
# Automatically creates safe placeholder .cpp files
# (for CI or bootstrap builds)
# ============================================================

SRC_DIR="src"

echo "🪶 [R3C] Generating stub sources in '$SRC_DIR'..."

mkdir -p "$SRC_DIR"

# 대상 파일 목록 (필요하면 여기에 추가)
files=(
  "main.cpp"
  "manifest.cpp"
  "formatter.cpp"
  "docgen.cpp"
)

for f in "${files[@]}"; do
  path="$SRC_DIR/$f"
  base=$(basename "$f" .cpp)
  func="r3c_stub_${base}"

  echo "  -> Creating stub: $path"
  {
    echo "// ======================================="
    echo "// Auto-generated stub for R3C component"
    echo "// File: $f"
    echo "// Generated at: $(date)"
    echo "// ======================================="
    echo ""
    echo "void ${func}() {}"
  } > "$path"
done

echo "✅ [R3C] Stub generation completed successfully."
