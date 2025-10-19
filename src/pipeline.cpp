// src/pipeline.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <sstream>

namespace fs = std::filesystem;

//----------------------------------------------------
// 공통 실행 함수
//----------------------------------------------------
static int exec_cmd(const std::string& cmd, const std::string& stage) {
    std::cout << "[R3C][" << stage << "] $ " << cmd << "\n";
    int ret = std::system(cmd.c_str());
    if (ret != 0) {
        std::cerr << "❌ Stage failed: " << stage << " (exit " << ret << ")\n";
        return ret;
    }
    std::cout << "✅ Stage done: " << stage << "\n";
    return 0;
}

//----------------------------------------------------
// 1️⃣ Rust → NASM
//----------------------------------------------------
static int stage_transpile(const std::string& input, const std::string& asm_out) {
    std::ofstream f(asm_out);
    if (!f.is_open()) {
        std::cerr << "❌ Cannot write ASM output: " << asm_out << "\n";
        return 1;
    }

    // TODO: 실제 Rust 파싱 → ASM 변환 로직 삽입
    f << "section .text\n"
      << "global _start\n"
      << "_start:\n"
      << "    mov rax, 60\n"
      << "    xor rdi, rdi\n"
      << "    syscall\n";
    f.close();

    std::cout << "[R3C] Generated dummy NASM file: " << asm_out << "\n";
    return 0;
}

//----------------------------------------------------
// 2️⃣ Assemble (NASM → .o)
//----------------------------------------------------
static int stage_assemble(const std::string& asm_out, const std::string& obj_out) {
#if defined(_WIN32)
    std::stringstream cmd;
    cmd << "nasm -f win64 \"" << asm_out << "\" -o \"" << obj_out << "\"";
#else
    std::stringstream cmd;
    cmd << "nasm -f elf64 \"" << asm_out << "\" -o \"" << obj_out << "\"";
#endif
    return exec_cmd(cmd.str(), "assemble");
}

//----------------------------------------------------
// 3️⃣ Link (.o → exe)
//----------------------------------------------------
static int stage_link(const std::string& obj_out, const std::string& exe_out) {
#if defined(_WIN32)
    std::stringstream cmd;
    cmd << "link /subsystem:console /entry:main /out:" << exe_out << " " << obj_out;
#else
    std::stringstream cmd;
    cmd << "ld -o " << exe_out << " " << obj_out;
#endif
    return exec_cmd(cmd.str(), "link");
}

//----------------------------------------------------
// 4️⃣ Execute
//----------------------------------------------------
static void stage_run(const std::string& exe_out) {
    std::cout << "[R3C][run] Executing " << exe_out << " ...\n";
#if defined(_WIN32)
    std::system(exe_out.c_str());
#else
    std::stringstream cmd;
    cmd << "./" << exe_out;
    std::system(cmd.str().c_str());
#endif
}

//----------------------------------------------------
// 5️⃣ 파이프라인 자동화
//----------------------------------------------------
int run_pipeline(const std::vector<std::string>& args,
                 const std::string& file,
                 bool emit_asm,
                 bool run_shell,
                 const std::string& output,
                 bool debug)
{
    std::cout << "=====================================================\n";
    std::cout << "[R3C] Auto Pipeline: Rust → NASM → OBJ → EXE\n";
    std::cout << "=====================================================\n";

    fs::create_directories("build");
    std::string asm_out = "build/out.asm";
    std::string obj_out = "build/out.o";
    std::string exe_out = output.empty() ? "build/out.exe" : output;

    // 자동 순서 실행
    if (int e = stage_transpile(file, asm_out)) return e;
    if (int e = stage_assemble(asm_out, obj_out)) return e;
    if (int e = stage_link(obj_out, exe_out)) return e;
    if (run_shell) stage_run(exe_out);

    std::cout << "=====================================================\n";
    std::cout << "[R3C] Pipeline finished successfully\n";
    std::cout << "=====================================================\n";
    return 0;
}
