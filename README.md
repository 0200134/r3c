![Build](https://github.com/0200134/r3c/actions/workflows/build.yml/badge.svg)
# 🦀 R3C — Rust → NASM Transpiler & Self-Bootstrap Compiler

![r3c_progress-0](https://img.shields.io/badge/Tasks_Completed-0-brightgreen)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Project Board](https://img.shields.io/badge/Project_Board-Active-success.svg)](https://github.com/0200134/r3c/projects/1)

---

## ⚙️ Overview

**R3C** aims to make **Rust fully independent** —  
a self-hosting compiler that converts **Rust → NASM → Executable**,  
completely **without LLVM, libc, or CRT**.

> 🔧 *“Rust independence, built line-by-line in NASM.”*

---

## 🧱 Architecture




[Rust Source]
↓
[Transpiler: r3c]
↓
[NASM Assembly]
↓
[Assembler: NASM]
↓
[Executable Binary]



- ✅  LLVM-free pipeline  
- ✅  Minimal runtime, no external libs  
- ✅  Bootstrappable (R3C builds itself)  
- ✅  CMake + NASM portable toolchain  

---

## 🚀 Build & Run

### Windows (MSVC / MinGW)
```bash
git clone https://github.com/0200134/r3c.git
cd r3c
cmake -B build -S .
cmake --build build
.\build\r3c.exe --emit-asm examples\sample.cpp



Linux (optional)


sudo apt install cmake nasm g++
cmake -B build -S .
cmake --build build
./build/r3c --emit-asm examples/sample.cpp




🧩 Features




Feature
Status
Description




Rust → NASM Transpilation
✅
Supports basic control flow (if/else/while)


NASM Bootstrap
✅
Can compile its own output


Std-less Runtime
🚧
Core runtime under development


Linux / ELF Support
🧠 Planned
Cross-target expansion


Optimization Passes
🔜
Constant folding, DCE, etc.





🧠 Philosophy


R3C isn’t “yet another compiler.”

It’s a Rust independence experiment —

to prove that a modern language can self-host,

without dragging a monolithic backend.



🤖 Automation




Workflow
Description




project-auto.yml
Automatically moves Issues/PRs to the Project Board


weekly-summary.yml
Updates task-count badge weekly


test-build.yml (planned)
Continuous Integration build test




Check the Project Board → R3C Compiler Development Board

for all active tasks, ideas, and milestones.



🤝 Contributing


We welcome all contributors — from bug fixers to bootstrap architects.


👉 See CONTRIBUTING Guide

👉 Open Issue Templates


Quick Start:


git clone https://github.com/0200134/r3c.git
cd r3c
git checkout -b feature/my-feature
cmake -B build -S .
cmake --build build



Once your PR is merged, automation will mark it as ✅ Done.



🧾 License


This project is licensed under the MIT License.

You’re free to use, modify, and distribute — just keep the license notice.



❤️ Contributors




Name
Contribution




@0200134
Creator / Maintainer


(you?)
Join via PR!







“One NASM line closer to Rust’s independence.”





---


---

---



