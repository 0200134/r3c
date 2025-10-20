# ⚙️ R3C Architecture Detail

> “The closer to metal, the closer to truth.”

---

## 🧩 1. Core Components Overview

| File | Description |
|------|--------------|
| `transpiler.cpp` | Analyzes Rust syntax and converts it into NASM assembly code. |
| `r3c.cpp` | Main entry point. Initializes the pipeline, parses CLI options, and executes the full build process. |
| `pkgmgr.cpp` | Package and dependency manager. Integrated with the `r3cpkg` CLI. |
| `manifest.cpp` | Parses project metadata from `r3c.toml` or `manifest.r3`. |
| `formatter.cpp` | Handles output formatting, string trimming, and token visualization. |
| `docgen.cpp` | *(Optional)* Auto-generates documentation and CLI summaries. |
| `r3cpkg.cpp` | Independent CLI tool for package installation, building, and path synchronization. |

---

## 🔩 2. Transpilation Pipeline (Rust → NASM)

The heart of R3C lies in `transpiler.cpp`.  
It receives Rust source code and processes it through several distinct phases to produce NASM assembly.




[Rust Source]
↓
[Lexer / Tokenizer]
↓
[Syntax Tree Builder]
↓
[Instruction Generator]
↓
[NASM Assembly Output]



- **Lexer** – Splits tokens (e.g., `fn`, `let`, `while`, `if`, `else`).
- **Parser** – Constructs the Abstract Syntax Tree (`AST`).
- **Emitter** – Maps AST nodes to NASM instructions.

Example:
```rust
let x = 5;



→


mov rax, 5
mov [x], rax





Optimizer (experimental) – Removes redundant MOV instructions and reuses registers when possible.





🧱 3. Build & Linking Pipeline


[R3C Output ASM]
     ↓
NASM Assembler
     ↓
Object File (.obj / .o)
     ↓
Linker (ld)
     ↓
Executable (EXE / ELF)



Goal: achieve a fully independent build chain with zero LLVM involvement.




Platform
Command Example




Windows
nasm -f win64 source.asm → link with ld


Linux
nasm -f elf64 source.asm → ld -dynamic-linker /lib64/ld-linux-x86-64.so.2





🧠 4. Token System


R3C is not a text-based translator — it uses a structured token tree model.




Token Type
Example
Description




FN
fn main()
Function definition start


LET
let a = 10
Local variable declaration


IF / ELSE
—
Conditional branching (mapped to jumps and comparisons)


WHILE
—
Loop construction (with labels and conditional jumps)


RETURN
—
Translated to ret instruction





🧰 5. Command Line Options




Command
Description




--emit-asm
Generate NASM assembly files.


--emit-asm-from-rust
Directly transpile from Rust source to ASM.


--asm-out <path>
Specify output directory for generated ASM.


--transpile-all
Transpile all source files within the project.


--run-pipeline
Run full pipeline (ASM → Object → Executable).


--verbose
Enable detailed logging output.





🔧 6. Package System (r3cpkg)


r3cpkg.cpp implements a Cargo-like package manager.


Example usage:


r3cpkg init
r3cpkg add rustlib/core
r3cpkg build





Stores metadata in manifest.r3 or r3c.toml.


Automatically fetches dependencies and configures include paths.


Planned feature: r3cpkg publish for registry uploads.





🧬 7. Manifest Format


[package]
name = "r3c"
version = "0.1.0"
edition = "lts-2025"

[build]
emit = ["asm", "exe"]
output = "build/out_lts"

[dependencies]
core = "r3c/core"
std = "r3c/std"




🚦 8. Error Handling System


R3C replaces C-style errno with a Rust-like Result model.


Result<R3CUnit, R3CError> transpile(const std::string& path);





Success: returns R3CUnit (contains AST and ASM output info).


Failure: returns R3CError (includes line, token, and error cause).




Example output:


[ERROR] unexpected token at line 12: "fn"




🧱 9. Planned Extensions




Feature
Goal
Status




Struct / Union
Map Rust structures to ASM memory blocks
🧩 Designing


Type System
Support for primitives (i32, f64, bool)
✅ Completed


Pattern Match
Convert match into jump tables
🚧 In progress


Function Pointer
Indirect register-based calls
✅ Supported


Bootstrap
Self-compile R3C with its own output
⏳ Preparing





💬 10. Design Philosophy




“The fewer the abstractions, the closer to metal.”

— R3C Manifesto




R3C is not just a Rust transpiler.

It is an experimental platform designed to prove that the structure and safety of Rust can exist without C or LLVM.


It preserves the minimalist spirit of C while inheriting Rust’s safety and expressiveness.



Document: docs/R3C_Architecture_Detail.md

Author: @0200134

Version: 0.1.0 LTS (2025-10)



---
