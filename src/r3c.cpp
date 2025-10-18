#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include "pkgmgr.hpp"

using namespace std;
namespace fs = std::filesystem;

// forward declarations
int run_pipeline(const vector<string>&, const string&, bool, bool, const string&, bool);
int pkg_main(int argc, char** argv);
int fmt_main();
int test_main();
int doc_main();

int main(int argc, char** argv) {
    if (argc > 1) {
        string cmd = argv[1];

        if (cmd == "pkg")  return pkg_main(argc - 1, argv + 1);
        if (cmd == "fmt")  return fmt_main();
        if (cmd == "test") return test_main();
        if (cmd == "doc")  return doc_main();

        if (cmd == "build" || cmd == "run" || cmd == "clean") {
            if (cmd == "clean") {
                fs::remove_all("build");
                cout << "[OK] cleaned\n";
                return 0;
            }
            vector<string> args;
            return run_pipeline(args, "", true, false, "build/out_lts.asm", true);
        }

        cerr << "[ERR] Unknown command: " << cmd << "\n";
        cerr << "Available: pkg, build, run, fmt, doc, test, clean\n";
        return 1;
    }

    // Default: interactive pipeline (manual input)
    vector<string> args;
    return run_pipeline(args, "", true, false, "build/out_lts.asm", true);
}
