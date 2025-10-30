# Contributing to R3C Foundation

💖 **Welcome to the R3C Ecosystem!**
R3C aims to build an LLVM-independent toolchain: translating C++ → Rust → NASM with full transparency and reproducibility.

---

## 🧭 Guidelines

1. **Respect the pipeline**
   - Core principle: *C++ is the root, Rust is the stem, ASM is the fruit.*
   - Do not mix unrelated compiler backends (LLVM, GCC, etc.) unless explicitly for comparison.

2. **Keep it reproducible**
   - Every change must build across Linux, macOS, and Windows.
   - If adding new code, provide a minimal test build (`make`, `cmake`, or `r3c build`).

3. **PR scope**
   - Prefer smaller PRs with clear purpose.
   - Examples:  
     ✅ Add missing stubs or headers  
     ✅ Improve CMake flags  
     ✅ Fix docs or build scripts  
     ❌ Massive refactors without discussion

4. **Branch naming**
   - `fix/*` for bug fixes  
   - `feat/*` for new functionality  
   - `ci/*` for workflow changes  
   - `doc/*` for documentation

5. **Code style**
   - Use 4 spaces, no tabs.  
   - Comment every non-obvious transformation.  
   - Prefer English for all public-facing code/comments.

---

## 🧪 Build Matrix

| OS | Compiler | Notes |
|----|-----------|-------|
| Ubuntu | GCC / Clang | Default CI target |
| macOS | Apple Clang | Used for Darwin verification |
| Windows | MSVC / Clang-CL | Tested for MSVC ABI parity |

---

## ⚙️ Sub-projects
| Name | Description |
|------|--------------|
| `r3c` | Core compiler & transpiler |
| `cpppm` | C++ package manager |
| `rust-ltss` | Rust LTSS frozen toolchain |
| `beyond-llvm` | LLVM-Zero backend experiments |

---

## 🪶 Submitting
- Fork the repo  
- Create a feature branch  
- Commit with conventional commit messages (`feat:`, `fix:`, `ci:`, etc.)  
- Open a PR to `main` branch  
- A maintainer will review it within a few days

Thanks for helping R3C evolve toward compiler sovereignty 🌸
