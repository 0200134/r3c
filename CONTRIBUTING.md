# Contributing to R3C

감사합니다. R3C 프로젝트는 오픈 Rust 3.0 사양을 목표로 하며, 누구나 기여할 수 있습니다.

---

## 🔧 개발 환경
- OS: Windows 10+, Linux (Ubuntu 22.04+)
- Toolchain:
  - CMake 3.12+
  - NASM 2.16+
  - clang++ 17+
  - Rust 1.65+ (optional, for r3clib.rs)
- 빌드:
  ```bash
  cmake -B build -S .
  cmake --build build
