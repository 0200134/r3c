
<!-- DASHBOARD_START -->
<!-- 이 아래 부분은 자동으로 갱신됩니다 -->
<!-- DASHBOARD_END -->

# 🦀 r3c — Rust LTS Transpiler + NASM Bootstrap

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/0200134/r3c/actions)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/0200134/r3c/blob/main/LICENSE)
[![Language](https://img.shields.io/badge/language-Rust%20%2B%20NASM-orange)](#)
[![Project Board](https://img.shields.io/badge/board-R3C%20Compiler%20Dev-blueviolet)](https://github.com/0200134/r3c/projects)
[![No C Allowed](https://img.shields.io/badge/C%20code-forbidden-red)](#)

> **No C. No LLVM. Only Rust and Assembly.**  
> _“C deserves rest — Rust must now walk on its own.”_

---

## 🧠 Philosophy

R3C isn’t *“yet another compiler.”*  
It’s a **Rust independence experiment** —  
to prove that a modern language can self-host  
without dragging a monolithic backend.

C built the world.  
R3C builds the next one — free from C, free from LLVM.

> “Respect the C.  
> Replace the dependency.  
> Rebuild the freedom.”

---

## ⚙️ Architecture Overview




Rust Source  ──▶  r3c  ──▶  NASM ASM  ──▶  OBJ  ──▶  EXE



- **Transpile:** Rust → NASM  
- **Assemble:** NASM → Object  
- **Link:** Direct OS API linking (no libc / CRT)  
- **Goal:** Full self-bootstrap (`r3c` builds `r3c`)

All builds are linear, deterministic, and fully independent.  
No C, no Clang, no LLVM in the pipeline.

---

## 🚫 C Language Policy

C is **forbidden** in this project.

| Forbidden | Reason |
|------------|--------|
| `#include <stdio.h>` | libc dependency |
| `malloc`, `free`, `printf` | CRT linkage |
| `main()` | legacy entry point |
| Any `.c` file | breaks independence |

> “We inherit C’s discipline — not its runtime.”

---

## 🤖 Automation

| Workflow | Description |
|-----------|-------------|
| `project-auto.yml` | Automatically moves Issues/PRs to the Project Board |
| `weekly-summary.yml` | Updates task-count badge weekly |
| `test-build.yml` *(planned)* | Continuous Integration build test |

🔗 **Project Board:** [R3C Compiler Development Board](https://github.com/0200134/r3c/projects)

---

## 🤝 Contributing

We welcome all contributors — from **bug fixers** to **bootstrap architects.**

### Rules
1. **No C.** Rust + NASM only.  
2. Follow the philosophy before writing code.  
3. Document every architectural decision.

👉 [CONTRIBUTING Guide](https://github.com/0200134/r3c/blob/main/CONTRIBUTING.md)  
👉 [Issue Templates](https://github.com/0200134/r3c/issues/new/choose)

### Quick Start

```bash
git clone https://github.com/0200134/r3c.git
cd r3c
git checkout -b feature/my-feature
cmake -B build -S .
cmake --build build



When your PR is merged, the automation will mark it as ✅ Done.



🧾 License


Licensed under the MIT License.

You’re free to use, modify, and distribute — just keep the license notice.



❤️ Contributors




Name
Role




@0200134
Creator / Maintainer


(you?)
Join via PR!






“One NASM line closer to Rust’s independence.”





🏁 Summary


R3C is not just another transpiler —

it’s the first step toward a self-hosted Rust world.




No C. No LLVM. Only Rust and Assembly.





---

