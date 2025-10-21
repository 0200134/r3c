#!/bin/bash
# ========================================
# R3C Stub Auto-Generator (v2)
# Compatible with macOS, Linux, Windows (Git Bash)
# ========================================

set -e

echo "🪶 [r3c] Generating safe stub sources..."

SRC_DIR="src"

# 파일 확장자를 제거하고 함수명에 '.'이 들어가지 않도록 처리
for path in ${SRC_DIR}/*.cpp; do
  name=$(basename "$path" .cpp)
  echo "void r3c_stub_${name}() {}" > "$path"
  echo "  ✅ generated stub: $path"
done

echo "✅ [r3c] Stub generation completed successfully."
