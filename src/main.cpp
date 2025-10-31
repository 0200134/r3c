#include "transpiler.hpp"
#include <iostream>
#include <string>

using namespace r3c;

int main(int argc, char** argv) {
    TranspileOptions opt;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--input" && i + 1 < argc) opt.input_path = argv[++i];
        else if (a == "--outdir" && i + 1 < argc) opt.out_dir = argv[++i];
        else if (a == "--self-heal") opt.self_heal = true;
        else if (a == "--no-emit-rust") opt.emit_rust = false;
        else if (a == "--no-emit-asm") opt.emit_asm = false;
        else if (a == "-h" || a == "--help") {
            std::cout << "R3C CLI Usage:\n"
                         "  --input <file>       Input C++ source file\n"
                         "  --outdir <dir>       Output directory (default: build/out)\n"
                         "  --self-heal          Enable automatic error correction\n"
                         "  --[no-]emit-rust     Emit Rust stub (default: on)\n"
                         "  --[no-]emit-asm      Emit NASM stub (default: on)\n";
            return 0;
        }
    }

    Transpiler t;
    return t.run(opt);
}
