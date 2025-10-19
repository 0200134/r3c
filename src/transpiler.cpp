// transpiler.cpp — Rust→NASM(Win64) C-free
// v4.3: no conflict with pipeline.cpp + callable entry
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "transpiler.hpp"

#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <filesystem>
#include <vector>
#include <set>
#include <map>
#include <optional>
#include <cctype>
#include <cstdlib>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;
namespace fs = std::filesystem;

// ---------- console helpers ----------
static void vt_on(){
#ifdef _WIN32
    DWORD m=0; HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    if(h!=INVALID_HANDLE_VALUE && GetConsoleMode(h,&m)) SetConsoleMode(h, m|0x0004);
#endif
}
static void ok (const string& s){ cout << "\x1b[32m[OK]\x1b[0m "  << s << "\n"; }
static void err(const string& s){ cerr << "\x1b[31m[ERR]\x1b[0m " << s << "\n"; }
static void step(const string& s){ cout<< "\x1b[35m[STEP]\x1b[0m " << s << "\n"; }
static void cmd (const string& s){ cout << "\x1b[33m[CMD]\x1b[0m " << s << "\n"; }
static void diag(const string& s){ cout << "[DIAG] " << s << "\n"; }
static void refa(const string& s){ cout << "\x1b[36m[REFACTOR]\x1b[0m " << s << "\n"; }

// ---------------------------------------------------------------------------
// (중략) — 내부 구조(Expr, Stmt, parse_rust, emit_win 등)는 그대로 유지
// ---------------------------------------------------------------------------

// ---------- pipeline entry ----------
int run_rust_pipeline(
    const std::string& rust_src,   // Rust source file (.rs)
    const std::string& asm_out,    // output assembly file path
    bool test_mode = false)        // test mode flag
{
    vt_on();
    cout << "=====================================================\n";
    cout << "[r3c] Rust→NASM transpiler pipeline (Win64)\n";
    cout << "=====================================================\n";

    if (!fs::exists(rust_src)) {
        err("file not found: " + rust_src);
        return 1;
    }

    diag("Rust source OK: " + rust_src);

    string rf = rust_src;
    string out_rf;
    if (auto_refactor_rust(rf, out_rf)) {
        rf = out_rf;
    }

    step("Parsing Rust file: " + rf);
    IR ir; ParseStats pst{};
    if (!parse_rust(rf, ir, pst)) {
        err("parse failed");
        return 1;
    }

    diag("fn=" + to_string(pst.cnt_fn) + ", main=" + to_string(pst.cnt_main) + ", test_attr=" + to_string(pst.cnt_test_attr));
    diag("let=" + to_string(pst.cnt_let) + ", println=" + to_string(pst.cnt_println) + ", print=" + to_string(pst.cnt_print));
    diag("if=" + to_string(pst.cnt_if) + ", else=" + to_string(pst.cnt_else) + ", end=" + to_string(pst.cnt_end));
    diag("while=" + to_string(pst.cnt_while) + ", for=" + to_string(pst.cnt_for) + ", return=" + to_string(pst.cnt_return));
    diag("call=" + to_string(pst.cnt_call) + ", sleep=" + to_string(pst.cnt_sleep) + ", fs.exists=" + to_string(pst.cnt_fsx));
    if (pst.warn_no_match > 0)
        diag("no-match lines=" + to_string(pst.warn_no_match) + " (tolerated)");

    ofstream asmf(asm_out, ios::binary);
    if (!asmf) {
        err("asm open fail");
        return 2;
    }
    emit_win(ir, asmf, test_mode);
    asmf.close();
    ok("NASM emitted: " + asm_out);

    step("Assembling...");
    if (!assemble(asm_out, "build/out.exe"))
        return 3;

    ok("Pipeline completed successfully.");
    return 0;
}

// ---------- optional CLI entry (for manual run) ----------
#ifdef R3C_STANDALONE
int main(int argc, char** argv)
{
    string rust_src = (argc > 1 ? argv[1] : "sample.rs");
    string asm_out  = (argc > 2 ? argv[2] : "build/out.asm");
    bool test_mode  = (argc > 3 && string(argv[3]) == "test");

    return run_rust_pipeline(rust_src, asm_out, test_mode);
}
#endif
