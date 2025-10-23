#include "transpiler.hpp"
#include <iostream>
#include <vector>
#include <string>

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
    using namespace std;

    cout << "🧩 R3C LLVM-Free Transpiler CLI" << endl;

    vector<string> files = { "example.cpp" };
    string lts_version = "v6.6-lts";
    bool self_recompile = false;
    bool emit_asm = true;
    string asm_out = "build/output.asm";
    bool skip_bootstrap = false;

    int result = run_pipeline(files, lts_version, self_recompile, emit_asm, asm_out, skip_bootstrap);

    if (result == 0)
        cout << "✅ Pipeline finished successfully." << endl;
    else
        cerr << "❌ Pipeline failed." << endl;

    return result;
}
