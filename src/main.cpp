// src/main.cpp
#include <iostream>

int main(int argc, char** argv) {
    std::cout << "🧩 R3C LLVM-Free Universal Build" << std::endl;
#if defined(_WIN32)
    std::cout << "Platform: Windows" << std::endl;
#elif defined(__APPLE__)
    std::cout << "Platform: macOS" << std::endl;
#elif defined(__linux__)
    std::cout << "Platform: Linux" << std::endl;
#else
    std::cout << "Platform: Unknown" << std::endl;
#endif
    return 0;
}
