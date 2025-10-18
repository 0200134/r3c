#include "transpiler.hpp"
#include <string>
#include <vector>
#include <iostream>

// R3C entry point function (no main conflict)
int r3c_entry(int argc, char** argv) {
    std::vector<std::string> args;
    args.reserve(argc);
    for (int i = 0; i < argc; ++i)
        args.emplace_back(argv[i]);

    const std::string asm_out = "build/out_lts.asm";

    std::cout << "=====================================================\n";
    std::cout << "[r3c] Rust LTS transpiler + NASM bootstrap pipeline\n";
    std::cout << "=====================================================\n";
    std::cout << "[STEP] Running pipeline...\n";

    int result = run_pipeline(args, "", true, true, asm_out, false);

    if (result == 0) {
        std::cout << "[OK] NASM generated successfully: " << asm_out << "\n";
    } else {
        std::cerr << "[FAIL] Pipeline failed with code " << result << "\n";
    }

    return result;
}
