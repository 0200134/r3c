#!/usr/bin/env bash
set -e

echo "🦀 [R3C] Full GitHub Setup Starting..."

mkdir -p .github/workflows scripts docs

##############################################
# 1. GitHub Actions (Linux + Windows build)
##############################################
cat > .github/workflows/release-auto.yml <<'YAML'
name: Auto Release (Linux + Windows)

on:
  push:
    tags:
      - 'v*.*.*'

jobs:
  build-linux:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Build on Linux
        run: |
          sudo apt-get update && sudo apt-get install -y cmake nasm
          cmake -B build -S .
          cmake --build build --config Release -j$(nproc)
          mkdir dist && cp build/r3c dist/r3c
          tar czf r3c-linux.tar.gz -C dist r3c
      - name: Upload (Linux)
        uses: softprops/action-gh-release@v2
        with:
          files: r3c-linux.tar.gz
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}

  build-windows:
    runs-on: windows-latest
    steps:
      - uses: actions/checkout@v4
      - name: Build on Windows
        shell: pwsh
        run: |
          cmake -B build -S .
          cmake --build build --config Release -- /m
          mkdir dist
          Copy-Item build\\Release\\r3c.exe dist\\r3c.exe
          Compress-Archive -Path dist\\* -DestinationPath r3c-win64.zip
      - name: Upload (Windows)
        uses: softprops/action-gh-release@v2
        with:
          files: r3c-win64.zip
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
YAML

##############################################
# 2. README 설치 블록 삽입 (중복 방지)
##############################################
if ! grep -q "Quick Start" README.md; then
cat >> README.md <<'MARKDOWN'

---

## ⚡ Quick Start

**Linux/macOS**
```bash
curl -L https://github.com/0200134/r3c/releases/latest/download/r3c-linux.tar.gz | tar xz
sudo mv r3c /usr/local/bin/
r3c --help
