#pragma once
#include <nlohmann/json.hpp>


#include <string>
#include <map>
using json = nlohmann::json;
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
    std::map<std::string, std::string> packages;
};
