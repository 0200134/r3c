// main.cpp — entry for r3c
#include "transpiler.hpp"
#include <string>
#include <vector>

int main(int argc, char** argv) {
    std::vector<std::string> args;
    args.reserve(argc);
    for (int i = 0; i < argc; ++i) args.emplace_back(argv[i]);

    const std::string asm_out = "build/out_lts.asm";
    return run_pipeline(args, "", true, true, asm_out, false);
}
