#include "pipeline.hpp"
#include "transpiler.hpp"
#include <iostream>

using namespace std;
using namespace r3c;

void run_pipeline(
    const vector<string>& inputs,
    const string& output,
    bool emit_asm,
    bool run_shell,
    const string& asm_out,
    bool verbose)
{
    Transpiler tp("v6.6-lts", verbose);
    bool ok = tp.run_full_pipeline(inputs, /*self_recompile=*/false, emit_asm, asm_out, /*skip_bootstrap=*/false);
    if (!ok) {
        cerr << "❌ run_pipeline failed" << endl;
        return;
    }

    if (run_shell) {
        cout << "⚙️  (placeholder) Running shell commands..." << endl;
        // Future extension for invoking rustc / linker / package steps
    }

    cout << "✅ run_pipeline finished" << endl;
}
