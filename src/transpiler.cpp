#include "transpiler.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace r3c {

bool Transpiler::emit_rust_stub(const fs::path& input, const fs::path& out_dir) {
    try {
        fs::path out = out_dir / (input.empty() ? "demo.rs" : input.stem().string() + ".rs");
        std::ofstream f(out);
        f << "// [R3C] Auto-generated Rust stub\n";
        f << "// Input: " << (input.empty() ? "(none)" : input.filename().string()) << "\n\n";
        f << "fn main() {\n";
        f << "    println!(\"Hello from R3C Rust stub!\");\n";
        f << "}\n";
        f.close();
        std::cout << "🦀 Rust stub emitted → " << out << "\n";
        return true;
    } catch (const std::exception& e) {
        std::cerr << "⚠️ emit_rust_stub failed: " << e.what() << "\n";
        return false;
    }
}

bool Transpiler::emit_nasm_stub(const fs::path& input, const fs::path& out_dir) {
    try {
        fs::path out = out_dir / (input.empty() ? "demo.asm" : input.stem().string() + ".asm");
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

int Transpiler::run(const TranspileOptions& opt) {
    try {
        fs::path out_dir = fs::absolute(opt.out_dir);
        if (!fs::exists(out_dir)) fs::create_directories(out_dir);

        fs::path input_path = opt.input_path.empty() ? fs::path() : fs::absolute(opt.input_path);

        std::cout << "🔧 Running R3C transpiler...\n";
        std::cout << "📁 Output dir: " << out_dir << "\n";

        if (opt.emit_rust) emit_rust_stub(input_path, out_dir);
        if (opt.emit_asm)  emit_nasm_stub(input_path, out_dir);

        std::cout << "✅ Transpile completed successfully.\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "💥 Transpiler run failed: " << e.what() << "\n";
        return 1;
    }
}

} // namespace r3c
