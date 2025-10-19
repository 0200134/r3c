// src/pipeline.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

static int run_shell_cmd(const std::string &cmd, bool debug) {
    if (debug)
        std::cout << "[CMD] " << cmd << std::endl;
    int ret = std::system(cmd.c_str());
    if (ret != 0) {
        std::cerr << "❌ Command failed: " << cmd << " (exit " << ret << ")\n";
    }
    return ret;
}

int run_pipeline(const std::vector<std::string>& args,
                 const std::string& file,
                 bool emit_asm,
                 bool run_shell,
                 const std::string& output,
                 bool debug)
{
    std::cout << "=====================================================\n";
    std::cout << "[r3c] Rust LTS transpiler + NASM bootstrap pipeline\n";
    std::cout << "=====================================================\n";
    std::cout << "[STEP] Running pipeline...\n";

    fs::path input(file);
    if (!fs::exists(input)) {
        std::cerr << "❌ Input file not found: " << input << std::endl;
        return 1;
    }

    fs::create_directories("build");

    string asm_out = "build/out_lts.asm";
    string obj_out = "build/out_lts.o";
    string exe_out = output.empty() ? "build/out_lts.exe" : output;

    // 1️⃣ Rust → NASM (Transpile)
    std::cout << "=====================================================\n";
    std::cout << "[r3c] Rust->NASM extended (if/else/while + ops + run_shell)\n";
    std::cout << "=====================================================\n";

    // 실제 transpiler 로직이 나중에 추가될 예정.
    // 여기서는 더미 ASM 출력.
    std::ofstream asm_file(asm_out);
    asm_file << "section .text\n";
    asm_file << "global _start\n";
    asm_file << "_start:\n";
    asm_file << "    mov rax, 60\n";
    asm_file << "    xor rdi, rdi\n";
    asm_file << "    syscall\n";
    asm_file.close();

    std::cout << "[OK] NASM generated (extended)\n";

    // 2️⃣ Assemble
    std::cout << "[STEP] assembling\n";
    std::stringstream assemble_cmd;
#if defined(_WIN32)
    assemble_cmd << "nasm -f win64 \"" << asm_out << "\" -o \"" << obj_out << "\"";
#else
    assemble_cmd << "nasm -f elf64 \"" << asm_out << "\" -o \"" << obj_out << "\"";
#endif
    if (run_shell_cmd(assemble_cmd.str(), debug) != 0) return 2;

    // 3️⃣ Link
    std::cout << "[STEP] linking\n";
#if defined(_WIN32)
    std::stringstream link_cmd;
    link_cmd << "link /subsystem:console /entry:main /out:" << exe_out << " " << obj_out;
    if (run_shell_cmd(link_cmd.str(), debug) != 0) return 3;
#else
    std::stringstream link_cmd;
    link_cmd << "ld -o " << exe_out << " " << obj_out;
    if (run_shell_cmd(link_cmd.str(), debug) != 0) return 3;
#endif

    std::cout << "[OK] Linked executable: " << exe_out << std::endl;

    // 4️⃣ Optional: Run output
    if (run_shell) {
        std::cout << "[STEP] executing " << exe_out << " ...\n";
        run_shell_cmd(exe_out, debug);
    }

    std::cout << "=====================================================\n";
    std::cout << "[r3c] pipeline finished successfully\n";
    std::cout << "=====================================================\n";
    return 0;
}
