#include "pipeline.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char** argv) {
    using namespace std;

    cout << "🧩 R3C LLVM-Free CLI Launcher (v6.6 LTS)" << endl;

    vector<string> files = { "example.cpp" };
    string version = "v6.6-lts";
    bool self_recompile = false;
    bool emit_asm = true;
    string asm_out = "build/output.asm";
    bool skip_bootstrap = false;

    int result = run_pipeline(files, version, self_recompile, emit_asm, asm_out, skip_bootstrap);

    if (result == 0)
        cout << "✅ Pipeline finished successfully." << endl;
    else
        cerr << "❌ Pipeline failed." << endl;

    return result;
}
