#pragma once
#include <string>
#include <vector>

// 🧩 R3C main pipeline executor
// Full pipeline entrypoint for CLI and tests
void run_pipeline(
    const std::vector<std::string>& inputs,   // Input source files
    const std::string& output,                // General output directory
    bool emit_asm,                            // Emit ASM output (Rust → ASM)
    bool run_shell,                           // Run shell commands (Rustc etc.)
    const std::string& asm_out,               // ASM output file path
    bool verbose                              // Verbose logging
);
