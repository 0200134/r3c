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
    using namespace std;
    using namespace r3c;

    cout << "🧩 R3C LLVM-Free Transpiler Test" << endl;

    // 샘플 입력 파일
    std::vector<std::string> sources = { "example.cpp" };

    // LTS 버전 (예시)
    std::string version = "v6.4-ultra";

    bool self_recompile = false;
    bool emit_asm = true;
    std::string asm_out = "build/output.asm";
    bool skip_bootstrap = false;

    int result = run_pipeline(
        sources,
        version,
        self_recompile,
        emit_asm,
        asm_out,
        skip_bootstrap
    );

    if (result == 0)
        cout << "✅ Pipeline finished successfully.\n";
    else
        cerr << "❌ Pipeline failed.\n";

    return result;
}
