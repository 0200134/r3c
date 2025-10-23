#include "transpiler.hpp"
#include <iostream>

using namespace std;
using namespace r3c;

int run_pipeline(
    const vector<string>& files,
    const string& lts_version,
    bool self_recompile,
    bool emit_asm,
    const string& asm_out,
    bool skip_bootstrap
) {
    Transpiler tp(lts_version, true);
    bool ok = tp.run_full_pipeline(files, self_recompile, emit_asm, asm_out, skip_bootstrap);
    return ok ? 0 : 1;
}

int run_pipeline(
    const vector<string>& files,
    const string& lts_version,
    bool self_recompile
) {
    return run_pipeline(files, lts_version, self_recompile, false, "", false);
}
