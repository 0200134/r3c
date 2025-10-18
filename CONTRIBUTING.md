# Contributing to R3C 🦀➡️⚙️

Welcome to **R3C (Rust→NASM Compiler)** — a project aiming to build a fully self-hosted, LLVM-free Rust transpiler and NASM bootstrap pipeline.

We welcome contributions from anyone interested in compilers, assembly generation, bootstrapping, and low-level systems programming.

---

## ⚙️ 1. Project Goals

R3C’s primary mission:
- Build **Rust → NASM → Binary** pipeline without LLVM, libc, or CRT.
- Make the compiler **self-hosting** (R3C can compile itself).
- Keep the build portable: **CMake + C++17 + NASM + MinGW (Windows)**.
- Provide reproducible builds and minimal runtime dependencies.

---

## 🚀 2. How to Contribute

### 🪞 Step-by-step workflow
1. **Fork** this repository  
   → Click the “Fork” button (top right).
2. **Clone** your fork  
   ```bash
   git clone https://github.com/<your-username>/r3c.git
   cd r3c
