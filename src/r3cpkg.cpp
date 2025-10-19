#include "pkgmgr.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <nlohmann/json.hpp>  // ✅ JSON 헤더 추가
#include "r3cpkg.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace fs = std::filesystem;

static std::string read_file(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        throw std::runtime_error("Cannot open file: " + path);
    }
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return buffer.str();
}

void r3c_pkg::load_index(const std::string& path) {
    std::string data = read_file(path);
    try {
        json j = json::parse(data);
        index.clear();
        for (auto& [k, v] : j.items()) {
            index[k] = v.get<std::string>();
        }
    } catch (const std::exception& e) {
        std::cerr << "[r3c-pkg] Failed to parse index: " << e.what() << std::endl;
    }
}

void r3c_pkg::save_index(const std::string& path) const {
    json j;
    for (const auto& [k, v] : index) {
        j[k] = v;
    }
    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        throw std::runtime_error("Cannot write file: " + path);
    }
    ofs << j.dump(2);
}

void r3c_pkg::add_package(const std::string& name, const std::string& version) {
    index[name] = version;
}

void r3c_pkg::remove_package(const std::string& name) {
    auto it = index.find(name);
    if (it != index.end()) {
        index.erase(it);
    } else {
        std::cerr << "[r3c-pkg] Package not found: " << name << std::endl;
    }
}

void r3c_pkg::list_packages() const {
    if (index.empty()) {
        std::cout << "[r3c-pkg] No packages registered.\n";
        return;
    }
    std::cout << "📦 Installed packages:\n";
    for (const auto& [k, v] : index) {
        std::cout << " - " << k << "@" << v << "\n";
    }
}

bool r3c_pkg::exists(const std::string& name) const {
    return index.find(name) != index.end();
}

std::string r3c_pkg::get_version(const std::string& name) const {
    auto it = index.find(name);
    if (it != index.end()) return it->second;
    return "";
}
