#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace r3c {

class Transpiler {
public:
    Transpiler(const std::string& lts_version, bool verbose = true);

    // 🧱 Stage 1: C++ → Rust
    bool cpp_to_rust(const std::filesystem::path& input,
                     const std::filesystem::path& output_dir);

    // ⚙️ Stage 2: Rust → ASM
    bool rust_to_asm(const std::filesystem::path& input,
                     const std::filesystem::path& asm_out);

    // 🧩 Pipeline integration
    bool run_full_pipeline(const std::vector<std::string>& files,
                           bool self_recompile,
                           bool emit_asm,
                           const std::string& asm_out,
                           bool skip_bootstrap);

private:
    std::string lts_version_;
    bool verbose_;
    bool bootstrap_checked_ = false;

    bool check_environment();
    bool perform_bootstrap();
    void log(const std::string& msg);
};

} // namespace r3c
