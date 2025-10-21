#!/bin/bash
# ==========================================
# R3C Stub Generator (Fixed for macOS / Linux / Windows)
# ==========================================

set -e
echo "🪶 [r3c] Generating safe stub sources..."

SRC_DIR="src"
mkdir -p "$SRC_DIR"

for path in ${SRC_DIR}/*.cpp; do
  [ -e "$path" ] || continue
  name=$(basename "$path" .cpp)
  echo "void r3c_stub_${name}() {}" > "$path"
  echo "  ✅ generated stub: $path"
done

echo "✅ [r3c] Stub generation complete."
