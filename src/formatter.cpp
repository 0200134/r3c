#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

// 한 줄 앞뒤 공백 제거
static inline std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t");
    return s.substr(start, end - start + 1);
}

// 들여쓰기 계산용 도우미
static inline std::string indent_str(int level) {
    return std::string(level * 4, ' '); // 4-space indentation
}

// 포매터 핵심: 하나의 파일을 정리
static void format_file(const fs::path& path) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "[r3c:fmt] Failed to open file: " << path << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) lines.push_back(line);
    in.close();

    std::vector<std::string> out;
    int indent = 0;
    bool in_block_comment = false;

    for (auto& raw : lines) {
        std::string s = trim(raw);

        // 블록 주석 감지
        if (s.find("/*") != std::string::npos) in_block_comment = true;
        if (in_block_comment) {
            out.push_back(indent_str(indent) + s);
            if (s.find("*/") != std::string::npos) in_block_comment = false;
            continue;
        }

        // 줄 주석 유지
        if (s.rfind("//", 0) == 0 || s.rfind(";", 0) == 0) {
            out.push_back(indent_str(indent) + s);
            continue;
        }

        // 빈 줄 제거 (연속 빈 줄 방지)
        if (s.empty()) {
            if (!out.empty() && out.back().empty()) continue;
            out.push_back("");
            continue;
        }

        // 블록 닫기 전 들여쓰기 감소
        if (!s.empty() && s[0] == '}') indent = std::max(0, indent - 1);

        out.push_back(indent_str(indent) + s);

        // 블록 열기 후 들여쓰기 증가
        if (s.find('{') != std::string::npos &&
            s.find('}') == std::string::npos)
            indent++;
    }

    // 파일 덮어쓰기
    std::ofstream outFile(path);
    for (auto& l : out) outFile << l << "\n";
    outFile.close();

    std::cout << "[r3c:fmt] formatted " << path.filename().string() << std::endl;
}

// main entry for CLI
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
