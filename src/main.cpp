#include <iostream>

int main(int argc, char** argv) {
    std::cout << "🧩 R3C Compiler (LLVM-Free Build System)" << std::endl;
    std::cout << "Platform: " 
#ifdef _WIN32
              << "Windows";
#elif defined(__APPLE__)
              << "macOS";
#else
              << "Linux";
#endif
    std::cout << std::endl;
    return 0;
}
