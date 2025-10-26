#include "transpiler.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

using namespace r3c;
namespace fs = std::filesystem;

int main(int argc, char** argv) {
    TranspileOptions opt;
    opt.emit_asm = true;
    opt.emit_rust = true;
    opt.out_dir = "build/out"; // 기본 출력 디렉토리

    // ===== CLI 인자 파싱 =====
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        if (a == "--input" && i + 1 < argc) opt.input_path = argv[++i];
        else if (a == "--outdir" && i + 1 < argc) opt.out_dir = argv[++i];
        else if (a == "--emit-asm") opt.emit_asm = true;
        else if (a == "--no-emit-asm") opt.emit_asm = false;
        else if (a == "--emit-rust") opt.emit_rust = true;
        else if (a == "--no-emit-rust") opt.emit_rust = false;
        else if (a == "-h" || a == "--help") {
            std::cout << "r3c_cli usage:\n"
                         "  --input <file>      input source (optional for demo)\n"
                         "  --outdir <dir>      output directory (default: build/out)\n"
                         "  --[no-]emit-asm     emit NASM file (default: on)\n"
                         "  --[no-]emit-rust    emit Rust stub (default: on)\n";
            return 0;
        }
    }

    // ===== 출력 디렉토리 자동 생성 =====
    try {
        fs::path out(opt.out_dir);
        if (!fs::exists(out)) {
            fs::create_directories(out);
            std::cout << "📁 Created output directory: " << out << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "❌ Failed to prepare out dir (" << opt.out_dir << "): " << e.what() << "\n";
        return 1;
    }

    // ===== Transpiler 실행 =====
    Transpiler t;
    return t.run(opt);
}

