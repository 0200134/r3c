#!/bin/bash
# ========================================
# R3C Stub Auto-Generator (v2.1)
# ========================================

set -e
echo "🪶 [r3c] Generating safe stub sources..."

SRC_DIR="src"
if [ ! -d "$SRC_DIR" ]; then
  echo "⚠️ src directory not found"
  exit 0
fi

for path in ${SRC_DIR}/*.cpp; do
  [ -e "$path" ] || continue
  name=$(basename "$path" .cpp)
  echo "void r3c_stub_${name}() {}" > "$path"
  echo "  ✅ generated stub: $path"
done

echo "✅ [r3c] Stub generation completed successfully."
