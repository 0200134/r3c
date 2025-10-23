#include "transpiler.hpp"
#include <iostream>

int run_pipeline(
    const std::vector<std::string>& files,
    const std::string& lts_version,
    bool self_recompile,
    bool emit_asm,
    const std::string& asm_out,
    bool skip_bootstrap
);

int run_pipeline(
    const std::vector<std::string>& files,
    const std::string& lts_version,
    bool self_recompile
);

int main(int argc, char** argv) {
    std::cout << "🧩 R3C LLVM-Free Transpiler Test" << std::endl;

    std::vector<std::string> inputs = { "example.cpp" };
    std::string version = "v6.5-ultra";

    int result = run_pipeline(inputs, version, false, true, "build/out.asm", false);

    if (result == 0)
        std::cout << "✅ Pipeline finished successfully." << std::endl;
    else
        std::cerr << "❌ Pipeline failed." << std::endl;

    return result;
}
