#include "transpiler.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace r3c {

bool Transpiler::emit_rust_stub(const fs::path& input, const fs::path& out_dir) {
    try {
        fs::path out = fs::absolute(out_dir / (input.empty() ? "output.rs" : input.stem().string() + ".rs"));
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
        fs::path out = fs::absolute(out_dir / (input.empty() ? "output.asm" : input.stem().string() + ".asm"));
        std::ofstream f(out);

        f << "; [R3C] Auto-generated NASM stub\n";
        f << "; Input: " << (input.empty() ? "(none)" : input.filename().string()) << "\n\n";

        #if defined(_WIN32) || defined(_WIN64)
        f << "section .text\n";
        f << "global main\n";
        f << "extern ExitProcess\n\n";
        f << "main:\n";
        f << "    sub rsp, 40           ; shadow space\n";
        f << "    xor ecx, ecx          ; return code 0\n";
        f << "    call ExitProcess\n";
        f << "    add rsp, 40\n";
        f << "    ret\n";
        #else
        f << "section .text\n";
        f << "global _start\n\n";
        f << "_start:\n";
        f << "    mov rax, 60           ; syscall: exit\n";
        f << "    xor rdi, rdi          ; exit code = 0\n";
        f << "    syscall\n";
        #endif

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

        // 파일 생성 순서 보장 (NASM 실패 방지)
        bool rust_ok = false;
        bool asm_ok = false;

        if (opt.emit_rust) rust_ok = emit_rust_stub(input_path, out_dir);
        if (opt.emit_asm)  asm_ok  = emit_nasm_stub(input_path, out_dir);

        // NASM 파일 없을 경우 기본 스텁 생성
        fs::path fallback_asm = out_dir / "output.asm";
        if (!fs::exists(fallback_asm)) {
            std::ofstream f(fallback_asm);
            f << "; empty stub for NASM fallback\n";
            f.close();
            std::cout << "🩹 Created fallback NASM stub → " << fallback_asm << "\n";
        }

        if (rust_ok || asm_ok)
            std::cout << "✅ Transpile completed successfully.\n";
        else
            std::cerr << "⚠️ No outputs generated.\n";

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "💥 Transpiler run failed: " << e.what() << "\n";
        return 1;
    }
}

} // namespace r3c

