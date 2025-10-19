#pragma once
#include <string>
#include <vector>
#include <cstdio>

inline void r3c_banner() {
    std::puts("=====================================================");
    std::puts("[r3c] Rust LTS transpiler + NASM bootstrap pipeline");
    std::puts("=====================================================");
}

int run_pipeline(const std::vector<std::string>& args,
                 const std::string& manifest,
                 bool emit_asm,
                 bool emit_rust,
                 const std::string& out_dir,
                 bool verbose);
