#pragma once
#include <string>
#include <vector>

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
