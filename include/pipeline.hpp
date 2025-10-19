#pragma once
#include <string>
#include <vector>

// R3C main pipeline executor
void run_pipeline(
    const std::vector<std::string>& inputs,
    const std::string& output,
    bool emit_asm,
    bool run_shell,
    const std::string& asm_out,
    bool verbose);
