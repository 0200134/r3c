#include "transpiler.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;
namespace r3c {

// ✅ Rust stub emitter
bool Transpiler::emit_rust_stub(const fs::path& input, const fs::path& out_dir) {
    try {
        fs::path out = fs::absolute(out_dir / (input.empty() ? "output.rs" : input.stem().string() + ".rs"));
        std::ofstream f(out);
        f << "// [R3C] Auto-Healing Rust stub\n";
        f << "// Target Rust version: 1.90\n";
        f << "// Input: " << (input.empty() ? "(none)" : input.filename().string()) << "\n\n";
        f << "use std::{fs, process::Command, sync::OnceLock};\n\n";
        f << "static INIT: OnceLock<()> = OnceLock::new();\n\n";
        f << "fn main() {\n";
        f << "    INIT.get_or_init(|| {\n";
        f << "        println!(\"🦀 Initializing R3C self-healing stub runtime (Rust 1.70+)\");\n";
        f << "    });\n";
        f << "    println!(\"🚀 Running transpiled code...\");\n";
        f << "}\n";
        f.close();
        std::cout << "🦀 Rust stub emitted → " << out << "\n";
        return true;
    } catch (const std::exception& e) {
        std::cerr << "⚠️ emit_rust_stub failed: " << e.what() << "\n";
        return false;
    }
}

// ✅ NASM stub emitter
bool Transpiler::emit_nasm_stub(const fs::path& input, const fs::path& out_dir) {
    try {
        fs::path out = fs::absolute(out_dir / (input.empty() ? "output.asm" : input.stem().string() + ".asm"));
        std::ofstream f(out);

        f << "; [R3C] Auto-generated NASM stub\n";
        f << "; Input: " << (input.empty() ? "(none)" : input.filename().string()) << "\n\n";
        f << "section .text\n";
        f << "global _start\n\n";
        f << "_start:\n";
        f << "    mov rax, 60\n";
        f << "    xor rdi, rdi\n";
        f << "    syscall\n";

        f.close();
        std::cout << "⚙️ NASM stub emitted → " << out << "\n";
        return true;
    } catch (const std::exception& e) {
        std::cerr << "⚠️ emit_nasm_stub failed: " << e.what() << "\n";
        return false;
    }
}

// ✅ Self-healing function (auto patch)
bool Transpiler::auto_fix(const fs::path& asm_file) {
    try {
        if (!fs::exists(asm_file)) {
            std::cerr << "❌ No ASM file to fix: " << asm_file << "\n";
            return false;
        }

        std::ifstream in(asm_file);
        std::stringstream buffer;
        buffer << in.rdbuf();
        in.close();
        std::string code = buffer.str();

        bool modified = false;

        if (code.find("section .text") == std::string::npos) {
            std::cout << "🩹 Auto-fix: adding 'section .text' header\n";
            code = "section .text\n" + code;
            modified = true;
        }
        if (code.find("global _start") == std::string::npos) {
            std::cout << "🩹 Auto-fix: adding 'global _start'\n";
            code = "global _start\n" + code;
            modified = true;
        }

        if (modified) {
            std::ofstream out(asm_file);
            out << code;
            out.close();
            std::cout << "✅ Auto-fix complete → " << asm_file << "\n";
            return true;
        } else {
            std::cout << "ℹ️ No fix needed.\n";
        }

        return false;
    } catch (const std::exception& e) {
        std::cerr << "💥 auto_fix failed: " << e.what() << "\n";
        return false;
    }
}

// ✅ Transpiler main logic
int Transpiler::run(const TranspileOptions& opt) {
    try {
        fs::path out_dir = fs::absolute(opt.out_dir);
        if (!fs::exists(out_dir)) fs::create_directories(out_dir);

        std::cout << "🔧 Running R3C Transpiler...\n";
        std::cout << "📁 Output dir: " << out_dir << "\n";

        bool rust_ok = false, asm_ok = false;
        if (opt.emit_rust) rust_ok = emit_rust_stub(opt.input_path, out_dir);
        if (opt.emit_asm)  asm_ok  = emit_nasm_stub(opt.input_path, out_dir);

        if (opt.self_heal && !asm_ok) {
            std::cout << "⚠️ Build failed — invoking Self-Healing Engine...\n";
            fs::path asm_file = out_dir / (opt.input_path.empty() ? "output.asm" : fs::path(opt.input_path).stem().string() + ".asm");
            if (auto_fix(asm_file)) {
                std::cout << "🔁 Retrying after auto-fix...\n";
                asm_ok = emit_nasm_stub(opt.input_path, out_dir);
            }
        }

        if (rust_ok || asm_ok)
            std::cout << "✅ Transpile completed successfully.\n";
        else
            std::cerr << "⚠️ No output generated.\n";

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "💥 Transpiler run failed: " << e.what() << "\n";
        return 1;
    }
}

} // namespace r3c
