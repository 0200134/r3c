#include "transpiler.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <cstdlib>

namespace fs = std::filesystem;

namespace r3c {

// ---- Rust 버전 감지 (Windows/Linux/macOS 호환) ----
std::string Transpiler::detect_rust_version() {
    try {
        std::string result;
        char buf[128];

#if defined(_WIN32)
        FILE* pipe = _popen("rustc --version", "r");
        if (!pipe) return "unknown";
        while (fgets(buf, sizeof(buf), pipe)) result += buf;
        _pclose(pipe);
#else
        FILE* pipe = popen("rustc --version", "r");
        if (!pipe) return "unknown";
        while (fgets(buf, sizeof(buf), pipe)) result += buf;
        pclose(pipe);
#endif

        std::regex re("rustc ([0-9]+)\\.([0-9]+)");
        std::smatch m;
        if (std::regex_search(result, m, re))
            return m[1].str() + "." + m[2].str();
    } catch (...) {}
    return "unknown";
}

// ---- Rust Stub 생성 ----
bool Transpiler::emit_rust_stub(const fs::path& input, const fs::path& out_dir) {
    try {
        const std::string rust_version = detect_rust_version();
        fs::path out = fs::absolute(out_dir / (input.empty() ? "output.rs" : input.stem().string() + ".rs"));
        std::ofstream f(out, std::ios::binary);
        if (!f) throw std::runtime_error("cannot open file");

        f << "// [R3C] Auto-generated Rust stub\n";
        f << "// Target Rust version: " << rust_version << "\n";
        f << "// Input: " << (input.empty() ? "(none)" : input.filename().string()) << "\n\n";

        int major = 0, minor = 0;
        if (sscanf(rust_version.c_str(), "%d.%d", &major, &minor) == 2 && (major > 1 || (major == 1 && minor >= 70))) {
            f << "use std::sync::OnceLock;\n\n";
            f << "static INIT: OnceLock<()> = OnceLock::new();\n\n";
            f << "fn main() {\n";
            f << "    INIT.get_or_init(|| println!(\"Initializing R3C stub runtime (Rust 1.70+)\"););\n";
            f << "    println!(\"Hello from R3C Rust stub (Rust 1.70.0+)\");\n";
            f << "}\n";
        } else {
            f << "fn main() {\n";
            f << "    println!(\"Hello from legacy R3C Rust stub (<Rust 1.70)\");\n";
            f << "}\n";
        }

        std::cout << "🦀 Rust stub emitted → " << out << " [target: " << rust_version << "]\n";
        return true;
    } catch (const std::exception& e) {
        std::cerr << "⚠️ emit_rust_stub failed: " << e.what() << "\n";
        return false;
    }
}

// ---- NASM Stub 생성 ----
bool Transpiler::emit_nasm_stub(const fs::path& input, const fs::path& out_dir) {
    try {
        fs::path out = fs::absolute(out_dir / (input.empty() ? "output.asm" : input.stem().string() + ".asm"));
        std::ofstream f(out, std::ios::binary);
        if (!f) throw std::runtime_error("cannot open file");

        f << "; [R3C] Auto-generated NASM stub\n";
        f << "; Compatible with Rust 1.70 relaxed asm! ordering\n";
        f << "; Input: " << (input.empty() ? "(none)" : input.filename().string()) << "\n\n";

#if defined(_WIN32) || defined(_WIN64)
        f << "section .text\n"
          << "global main\n"
          << "extern ExitProcess\n\n"
          << "main:\n"
          << "    sub rsp, 40\n"
          << "    xor ecx, ecx\n"
          << "    call ExitProcess\n"
          << "    add rsp, 40\n"
          << "    ret\n";
#else
        f << "section .text\n"
          << "global _start\n\n"
          << "_start:\n"
          << "    mov rax, 60\n"
          << "    xor rdi, rdi\n"
          << "    syscall\n";
#endif

        std::cout << "⚙️ NASM stub emitted → " << out << "\n";
        return true;
    } catch (const std::exception& e) {
        std::cerr << "⚠️ emit_nasm_stub failed: " << e.what() << "\n";
        return false;
    }
}

// ---- 실행 ----
int Transpiler::run(const TranspileOptions& opt) {
    try {
        fs::path out_dir = fs::absolute(opt.out_dir);
        if (!fs::exists(out_dir)) fs::create_directories(out_dir);
        fs::path input_path = opt.input_path.empty() ? fs::path() : fs::absolute(opt.input_path);

        std::cout << "🔧 Running R3C transpiler...\n";
        std::cout << "📁 Output dir: " << out_dir << "\n";

        bool rust_ok = false;
        bool asm_ok  = false;

        if (opt.emit_rust) rust_ok = emit_rust_stub(input_path, out_dir);
        if (opt.emit_asm)  asm_ok  = emit_nasm_stub(input_path, out_dir);

        if (!fs::exists(out_dir / "output.asm")) {
            std::ofstream f(out_dir / "output.asm");
            f << "; fallback stub\n";
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
