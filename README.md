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



---

## 🧩 Contributions Welcome

R3C는 **Rust 3.0 Industrial LTS Compiler**를 지향하는 오픈소스 프로젝트입니다.  
누구나 자유롭게 기여할 수 있으며, 코드·문서·아이디어 모두 환영합니다!

<p align="center">
  <img src="https://img.shields.io/badge/Contributions-Welcome-4CAF50?style=for-the-badge&logo=github" alt="Contributions Welcome"/>
  <img src="https://img.shields.io/badge/License-MIT-blue?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Language-Rust%20%7C%20C++%20%7C%20NASM-orange?style=for-the-badge"/>
</p>

---

### 🤝 How to Contribute
1. **Fork** this repo  
2. **Create a branch** — `feature/<기능명>`  
3. **Commit** your changes  
4. **Open a Pull Request (PR)**  
5. **Wait for review & merge**

> 📘 자세한 절차는 [CONTRIBUTION_GUIDE.md](./docs/CONTRIBUTION_GUIDE.md) 를 참고하세요.

---

### 🧠 Quick Links
- [🐛 Bug Report](./.github/ISSUE_TEMPLATE/bug_report.yml)
- [💡 Feature Request](./.github/ISSUE_TEMPLATE/feature_request.yml)
- [📘 Spec Proposal](./.github/ISSUE_TEMPLATE/spec_proposal.yml)
- [📄 Pull Request Template](./.github/pull_request_template.md)

---

> 💬 *“No LLVM, No Borrow Checker Overhead — Just Rust, from Rust.”*  
> — Together, we build **Rust 3.0 Industrial Edition** 🦀
