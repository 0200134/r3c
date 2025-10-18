#include "transpiler.hpp"
#include "r3c_build_info.hpp"
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char** argv) {
    std::vector<std::string> args;
    args.reserve(argc);
    for (int i = 0; i < argc; ++i)
        args.emplace_back(argv[i]);

    // -------------------------
    // --version / --about 지원
    // -------------------------
    if (argc > 1) {
        const std::string arg = args[1];
        if (arg == "--version") {
            std::cout << "r3c v" << R3C_VERSION
                      << " (" << R3C_GIT_HASH
                      << ", built " << R3C_BUILD_DATE << ")\n";
            return 0;
        }
        if (arg == "--about") {
            std::cout << "R3C Build Info\n"
                      << "---------------------------\n"
                      << "Version    : " << R3C_VERSION << "\n"
                      << "Git Hash   : " << R3C_GIT_HASH << "\n"
                      << "Build Date : " << R3C_BUILD_DATE << "\n"
                      << "Platform   : " << R3C_PLATFORM << "\n"
                      << "Compiler   : " << R3C_COMPILER_NAME
                      << " " << R3C_COMPILER_VERSION << "\n"
                      << "NASM       : " << R3C_NASM_VERSION << "\n";
            return 0;
        }
    }

    // -------------------------
    // 기본 파이프라인 실행
    // -------------------------
    const std::string asm_out = "build/out_lts.asm";
    return run_pipeline(args, "", true, true, asm_out, false);
}
