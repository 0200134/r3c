// src/main.cpp
#include <iostream>

int main(int argc, char** argv) {
    std::cout << "🧩 R3C LLVM-Free Compiler Entry" << std::endl;
#if defined(__APPLE__)
    std::cout << "Running on macOS (AppleClang)" << std::endl;
#elif defined(_WIN32)
    std::cout << "Running on Windows (MSVC)" << std::endl;
#elif defined(__linux__)
    std::cout << "Running on Linux (GCC/Clang)" << std::endl;
#else
    std::cout << "Running on Unknown Platform" << std::endl;
#endif
    return 0;
}
