#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

// 한 파일 포매팅 로직
static void format_file(const fs::path& path) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "[r3c:fmt] Cannot open file: " << path << "\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        // 간단 trim
        while (!line.empty() && (line.back() == ' ' || line.back() == '\t'))
            line.pop_back();
        lines.push_back(line);
    }
    in.close();

    std::ofstream out(path);
    for (auto& l : lines) out << l << "\n";
    out.close();

    std::cout << "[r3c:fmt] formatted: " << path << "\n";
}

// ✅ 여기서 진입점 정의
int fmt_main() {
    std::cout << "[r3c:fmt] Formatter running...\n";
    const fs::path targetDir = "src";
    if (!fs::exists(targetDir)) {
        std::cerr << "[r3c:fmt] No 'src' directory found.\n";
        return 1;
    }

    int count = 0;
    for (auto& p : fs::recursive_directory_iterator(targetDir)) {
        if (p.path().extension() == ".rs" || p.path().extension() == ".asm") {
            format_file(p.path());
            count++;
        }
    }

    std::cout << "[r3c:fmt] Done. " << count << " file(s) formatted.\n";
    return 0;
}
