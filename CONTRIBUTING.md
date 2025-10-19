🧩 Contributing to R3C


Thank you for your interest in R3C (Rust Runtime Recompiler & Cross-compiler).

R3C is an open experiment to prove that a modern compiler can self-host without C or LLVM.


Your contribution — no matter how small — helps evolve this project into an independent, industrial-grade compiler toolchain.



⚙️ Quick Setup


git clone https://github.com/0200134/r3c.git
cd r3c
cmake -B build -S .
cmake --build build



To test locally:


./build/r3c --emit-asm --emit-asm-from-rust --asm-out build/out.asm




🧠 Contribution Areas


You can contribute in many ways:




Area
Task Example
Difficulty




🧠 Parser Engine
Add support for new Rust syntax: match, enum, impl, mod, etc.
🟡 Medium


⚙️ Backend / Emitter
Add emit_linux() to output ELF64 NASM and test on Ubuntu.
🔴 Hard


🧩 Refactor Engine
Improve auto_refactor_rust() rules, handle unused imports/variables.
🟡 Medium


🧾 Docs & Comments
Add function headers (/// AutoDoc), fix typos, improve explanations.
🟢 Easy


🧪 Tests
Add .rs test files under /tests/ and link them in CI.
🟡 Medium


🧱 Diagnostics
Enhance error messages and [STEP]/[ERR] color formatting.
🟢 Easy


🎨 Design / Branding
Improve R3C logo, badges, and README presentation.
🟢 Easy


🔒 Security Review
Harden file handling and system() usage, sandbox assembly calls.
🔴 Hard





🪄 Code Style




Language: C++17


Indentation: 4 spaces, no tabs


Line endings: LF (\n)


Encoding: UTF-8 (no BOM)


Naming: snake_case for functions, CamelCase for structs/classes


Logging: use ok(), err(), step(), diag() — no printf





🧪 Testing


R3C includes test automation via GitHub Actions (Linux/Mac/Windows).


Add new tests under tests/ as simple Rust examples:


fn main() {
    let mut x = 0;
    for i in 0..5 {
        x += i;
    }
    println!("{}", x);
}



Then confirm:


cmake --build build --target r3c_tests




🧾 Pull Request Rules




Fork → Branch → PR

git checkout -b feature/your-feature





Keep commits atomic and descriptive.

Example:

[parser] add match-expression support
[test] add rust/while_loop.rs sample





Run all builds before submitting:

cmake --build build --parallel





PR titles should be clear and scoped:

[refactor] cleanup parse_rust() logs





PRs that pass all CI builds are merged automatically.





❤️ Recognition


All accepted contributors appear automatically in:




README.md under ❤️ Contributors


AUTHORS.md (generated periodically)


GitHub “Contributors” panel





💬 Community




Issues: for bug reports, features, discussions


Pull Requests: for code or docs


Discussions: general talk, proposals, and experiments




If you have any creative idea — compiler design, new architecture, or meme-worthy philosophy — open a discussion under #r3c-core.



🦾 “Show, Don’t Tell.”




R3C’s principle is not talk — it’s proof by code.

If it builds, it counts. If it runs, it matters.


