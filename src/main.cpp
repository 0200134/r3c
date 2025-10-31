#include "transpiler.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    r3c::TranspileOptions opt;
    opt.out_dir = "build/out";
    opt.emit_asm = true;
    opt.emit_rust = true;

    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        if (a == "--input" && i + 1 < argc) opt.input_path = argv[++i];
        else if (a == "--outdir" && i + 1 < argc) opt.out_dir = argv[++i];
        else if (a == "--emit-asm") opt.emit_asm = true;
        else if (a == "--no-emit-asm") opt.emit_asm = false;
        else if (a == "--emit-rust") opt.emit_rust = true;
        else if (a == "--no-emit-rust") opt.emit_rust = false;
        else if (a == "-h" || a == "--help") {
            std::cout <<
                "r3c transpiler CLI usage:\n"
                "  --input <file>      input source (optional)\n"
                "  --outdir <dir>      output directory (default: build/out)\n"
                "  --[no-]emit-asm     emit NASM file (default: on)\n"
                "  --[no-]emit-rust    emit Rust stub (default: on)\n";
            return 0;
        }
    }

    try {
        fs::path out(opt.out_dir);
        if (!fs::exists(out)) {
            fs::create_directories(out);
            std::cout << "📁 Created output directory: " << out << "\n";
        }

        r3c::Transpiler t;
        return t.run(opt);
    } catch (const std::exception& e) {
        std::cerr << "❌ CLI error: " << e.what() << "\n";
        return 1;
    }
}
