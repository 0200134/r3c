#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "r3c.hpp"   // run_pipeline() 선언이 여기에 있다고 가정

namespace fs = std::filesystem;

static void print_help() {
    std::cout <<
    "R3C Compiler (Rust LTS → NASM Bootstrap)\n"
    "-----------------------------------------\n"
    "Usage:\n"
    "  r3c [options] <source>\n\n"
    "Options:\n"
    "  --emit-asm        Generate NASM assembly file\n"
    "  --run             Run the compiled program after linking\n"
    "  --out <file>      Set output executable path\n"
    "  --debug           Print all commands during pipeline\n"
    "  -h, --help        Show this help\n"
    "\nExample:\n"
    "  r3c --emit-asm --run examples/hello.rs\n";
}

//---------------------------------------------------------
// Main entry
//---------------------------------------------------------
int main(int argc, char** argv) {
    if (argc < 2) {
        print_help();
        return 1;
    }

    bool emit_asm = false;
    bool run_shell = false;
    bool debug = false;
    std::string output = "";
    std::string input = "";

    std::vector<std::string> args(argv + 1, argv + argc);

    for (size_t i = 0; i < args.size(); ++i) {
        const std::string& arg = args[i];

        if (arg == "--emit-asm") emit_asm = true;
        else if (arg == "--run") run_shell = true;
        else if (arg == "--debug") debug = true;
        else if (arg == "--out" && i + 1 < args.size()) {
            output = args[++i];
        }
        else if (arg == "-h" || arg == "--help") {
            print_help();
            return 0;
        }
        else if (arg[0] != '-') {
            input = arg;
        }
    }

    if (input.empty()) {
        std::cerr << "❌ No input file provided.\n";
        print_help();
        return 1;
    }

    if (!fs::exists(input)) {
        std::cerr << "❌ Source file not found: " << input << "\n";
        return 1;
    }

    std::cout << "=====================================================\n";
    std::cout << "[R3C] Input: " << input << "\n";
    std::cout << "[R3C] emit_asm=" << emit_asm 
              << ", run_shell=" << run_shell 
              << ", debug=" << debug << "\n";
    std::cout << "=====================================================\n";

    // run_pipeline() 자동 실행
    return run_pipeline(args, input, emit_asm, run_shell, output, debug);
}
