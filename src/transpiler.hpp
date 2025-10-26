#pragma once
#include <string>
#include <filesystem>

namespace r3c {

struct TranspileOptions {
    std::string input_path;
    std::string out_dir = "build/out";
    bool emit_asm = true;
    bool emit_rust = true;
};

class Transpiler {
public:
    int run(const TranspileOptions& opt);

private:
    bool emit_rust_stub(const std::filesystem::path& input, const std::filesystem::path& out_dir);
    bool emit_nasm_stub(const std::filesystem::path& input, const std::filesystem::path& out_dir);
};

} // namespace r3c
