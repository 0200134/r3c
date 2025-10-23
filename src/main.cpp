#include "pipeline.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char** argv) {
    using namespace std;
    cout << "🧩 R3C CLI start" << endl;

    vector<string> inputs = { "example.cpp" };
    string version = "v6.6-lts";
    bool self_recompile = false;
    bool emit_asm = true;
    string asm_out = "build/output.asm";
    bool skip_bootstrap = false;

    int result = run_pipeline(inputs, version, self_recompile, emit_asm, asm_out, skip_bootstrap);

    if (result == 0)
        cout << "✅ Pipeline finished successfully.\n";
    else
        cerr << "❌ Pipeline failed.\n";

    return result;
}
