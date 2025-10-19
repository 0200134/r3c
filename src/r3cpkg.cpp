#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <nlohmann/json.hpp>   // ✅ 반드시 포함
using json = nlohmann::json;  // ✅ 반드시 선언

class r3c_pkg {
public:
    void load_index(const std::string& path);
    void save_index(const std::string& path) const;
    void add_package(const std::string& name, const std::string& version);
    void remove_package(const std::string& name);
    void list_packages() const;
    bool exists(const std::string& name) const;
    std::string get_version(const std::string& name) const;

private:
    json index;
};

// ✅ 인덱스 로드
void r3c_pkg::load_index(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        std::cerr << "⚠️  Failed to open package index: " << path << std::endl;
        index = json::object();
        return;
    }

    try {
        index = json::parse(ifs);
    } catch (...) {
        std::cerr << "⚠️  Invalid JSON format in index file." << std::endl;
        index = json::object();
    }
}

// ✅ 인덱스 저장
void r3c_pkg::save_index(const std::string& path) const {
    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        std::cerr << "⚠️  Failed to save package index: " << path << std::endl;
        return;
    }

    ofs << index.dump(2);
}

// ✅ 패키지 추가
void r3c_pkg::add_package(const std::string& name, const std::string& version) {
    index[name] = version;
    std::cout << "📦 Added package: " << name << "@" << version << std::endl;
}

// ✅ 패키지 제거
void r3c_pkg::remove_package(const std::string& name) {
    if (index.contains(name)) {
        index.erase(name);
        std::cout << "🗑️  Removed package: " << name << std::endl;
    } else {
        std::cout << "⚠️  Package not found: " << name << std::endl;
    }
}

// ✅ 패키지 목록 표시
void r3c_pkg::list_packages() const {
    if (index.empty()) {
        std::cout << "(no packages installed)" << std::endl;
        return;
    }

    for (auto& [k, v] : index.items()) {
        std::cout << k << "@" << v << std::endl;
    }
}

// ✅ 존재 여부 확인
bool r3c_pkg::exists(const std::string& name) const {
    return index.contains(name);
}

// ✅ 버전 조회
std::string r3c_pkg::get_version(const std::string& name) const {
    if (index.contains(name))
        return index[name];
    return "";
}
