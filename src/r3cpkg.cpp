// r3cpkg.cpp (요약)
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void loadIndex(const std::string& file) {
    std::ifstream f(file);
    if (!f.is_open()) return;

    json j;
    f >> j; // ✅ now works

    for (auto& [k, v] : j.items())
        index[k] = v.get<std::string>();
}

void saveIndex(const std::string& file) {
    json j;
    for (auto& [k, v] : index)
        j[k] = v;

    std::ofstream f(file);
    f << j.dump(2); // ✅ now works
}
