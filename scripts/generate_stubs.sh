#!/usr/bin/env bash
set -e

# ================================================
# 🧱 R3C Stub Generator (fixed)
# Creates valid C++ stub files to prevent link errors.
# ================================================

SRC_DIR="src"
mkdir -p "$SRC_DIR"

files=(
  "docgen.cpp"
  "formatter.cpp"
  "main.cpp"
  "manifest.cpp"
)

echo "⚙️ [R3C] Generating stub source files in $SRC_DIR..."

for f in "${files[@]}"; do
  path="$SRC_DIR/$f"
  base=$(basename "$f" .cpp)
  func="r3c_stub_${base}"

  echo "🧩 Generating stub: ${func}() -> $path"
  echo "void ${func}() {}" > "$path"
done

echo "✅ Stub generation complete. (${#files[@]} files)"
