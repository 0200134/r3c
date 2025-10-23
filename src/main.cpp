#include "pipeline.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char** argv) {
    std::cout << "🧩 R3C CLI (v6.6 LTS)" << std::endl;

    std::vector<std::string> files = { "example.cpp" };
    std::string version = "v6.6-lts";
    bool self_recompile = false;
    bool emit_asm = true;
    std::string asm_out = "build/output.asm";
    bool skip_bootstrap = false;

    int result = run_pipeline(files, version, self_recompile, emit_asm, asm_out, skip_bootstrap);

    if (result == 0)
        std::cout << "✅ Build completed successfully." << std::endl;
    else
        std::cerr << "❌ Pipeline failed with code " << result << std::endl;

    return result;
}
