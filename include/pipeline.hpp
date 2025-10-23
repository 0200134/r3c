#pragma once
#include <string>
#include <vector>

// 🧩 Unified pipeline entrypoint for R3C CLI
int run_pipeline(
    const std::vector<std::string>& inputs,   // Input sources
    const std::string& lts_version,           // Version tag
    bool self_recompile,                      // Recompile flag
    bool emit_asm,                            // Generate ASM output
    const std::string& asm_out,               // ASM output path
    bool skip_bootstrap                       // Skip bootstrap init
);
