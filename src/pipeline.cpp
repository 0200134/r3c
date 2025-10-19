#include "pipeline.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void run_pipeline(
    const std::vector<std::string>& inputs,
    const std::string& output,
    bool emit_asm,
    bool run_shell,
    const std::string& asm_out,
    bool verbose)
{
    std::cout << "[r3c-pipeline] Starting pipeline..." << std::endl;

    if (inputs.empty()) {
        std::cerr << "[r3c] no input files provided." << std::endl;
        return;
    }

    for (const auto& src : inputs) {
        std::cout << "  -> processing: " << src << std::endl;
        if (!fs::exists(src)) {
            std::cerr << "  !! missing file: " << src << std::endl;
            continue;
        }
    }

    if (emit_asm) {
        std::cout << "  [emit] generating assembly: " << asm_out << std::endl;
    }

    if (run_shell) {
        std::cout << "  [exec] running system build step..." << std::endl;
        // system("nasm ...");
    }

    std::cout << "  [out] output: " << output << std::endl;
    std::cout << "[r3c-pipeline] Done." << std::endl;
}
