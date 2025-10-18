#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

int run_pipeline(const std::vector<std::string>&,
                 const std::string&,
                 bool,
                 bool,
                 const std::string&,
                 bool);

int test_main() {
    namespace fs = std::filesystem;
    int failed = 0, ran = 0;

    for (auto& p : fs::directory_iterator("tests")) {
        if (p.path().extension() == ".rs") {
            std::cout << "[TEST] " << p.path().string() << "\n";

            if (run_pipeline({}, "", true, false, "build/out_lts.asm", false) != 0) {
                std::cout << "[FAIL] " << p.path().string() << "\n";
                failed++;
            } else {
                std::cout << "[OK]\n";
            }

            ran++;
        }
    }

    std::cout << "[SUMMARY] " << ran << " run, " << failed << " failed\n";
    return failed ? 1 : 0;
}
