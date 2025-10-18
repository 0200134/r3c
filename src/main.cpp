#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include "pkgmgr.hpp"

// r3c.cpp에서 가져오는 함수
int r3c_entry(int argc, char** argv);

int run_pipeline(const std::vector<std::string>&, const std::string&, bool, bool, const std::string&, bool);
int pkg_main(int argc, char** argv);
int fmt_main();
int test_main();
int doc_main();

int main(int argc, char** argv) {
    if (argc > 1) {
        std::string cmd = argv[1];
        if (cmd == "pkg")  return pkg_main(argc - 1, argv + 1);
        if (cmd == "fmt")  return fmt_main();
        if (cmd == "test") return test_main();
        if (cmd == "doc")  return doc_main();
        if (cmd == "build" || cmd == "run" || cmd == "clean") {
            if (cmd == "clean") {
                std::filesystem::remove_all("build");
                std::cout << "[OK] cleaned\n";
                return 0;
            }
            return r3c_entry(argc, argv);
        }
    }

    // 기본 동작: r3c 파이프라인 실행
    return r3c_entry(argc, argv);
}
