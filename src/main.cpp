#include <iostream>

int main(int argc, char** argv) {
    std::cout << "🧩 R3C (LLVM-Free Compiler Framework)" << std::endl;
    std::cout << "Platform: "
#ifdef _WIN32
              << "Windows";
#elif defined(__APPLE__)
              << "macOS";
#else
              << "Linux";
#endif
    std::cout << std::endl;

    // 간단한 실행 테스트
    std::cout << "Arguments: " << argc << std::endl;
    for (int i = 0; i < argc; ++i)
        std::cout << "  [" << i << "] " << argv[i] << std::endl;

    return 0;
}
