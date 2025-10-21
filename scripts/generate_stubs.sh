#!/usr/bin/env bash
set -e

# ================================================
# 🧱 R3C Stub Generator (scripts/generate_stubs.sh)
# Generates minimal safe stub .cpp files to avoid build errors.
# ================================================

SRC_DIR="src"
mkdir -p "$SRC_DIR"

# Stub 대상 파일 목록
files=(
  "r3c.cpp"
  "r3c_stub.cpp"
  "pkgmgr.cpp"
  "pipeline.cpp"
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

