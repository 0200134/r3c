# r3c

# 🦀 r3c — Rust LTS Transpiler + NASM Bootstrap Pipeline

**r3c**는 Rust 코드를 직접 NASM 어셈블리어로 변환하고,  
C나 LLVM에 의존하지 않고 독립적으로 실행 파일을 만드는 **C-free Rust LTS 트랜스파일러**입니다.

---

## ✨ 특징

- ✅ **C-free** — libc, CRT, LLVM 없이 WinAPI 직접 호출  
- 🧠 **Rust-to-NASM transpilation** — Rust 문법을 직접 어셈블리어로 매핑  
- ⚙️ **Bootstrap 가능** — 자기 자신을 NASM으로 빌드 가능  
- 🔍 **Diagnostics** — 코드 구조, brace 불균형, 함수/변수 수 등 자동 점검  
- 🪶 **Auto Refactor** — 불필요한 공백과 들여쓰기 자동 정리  
- 🧪 **Test Mode** — `test` 모드로 문법 및 출력 검증  
- 📦 **No External Dependency** — CMake + NASM + MinGW만 있으면 동작  

---

## 🏗️ 빌드 방법

### 1️⃣ 의존성 설치
- [CMake](https://cmake.org/download/)
- [NASM](https://www.nasm.us/)
- [MinGW-w64](https://winlibs.com/)

### 2️⃣ 빌드 & 실행
```bash
cmake -B build -S .
cmake --build build
.\build\r3c.exe
