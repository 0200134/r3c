#!/usr/bin/env bash
set -e

# ================================================
# 🧱 R3C Stub Generator (syntax fix)
# ================================================

SRC_DIR="src"
mkdir -p "$SRC_DIR"

files=(
  "r3c.cpp"
  "r3c_stub.cpp"
  "pkgmgr.cpp"
  "pipeline.cpp"
  "docgen.cpp"
  "formatter.cpp"
  "manifest.cpp"
  "main.cpp"
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



  echo "🧩 Generating stub: ${func}() -> $path"
  echo "void ${func}() {}" > "$path"
done

echo "✅ Stub generation complete. (${#files[@]} files)"
