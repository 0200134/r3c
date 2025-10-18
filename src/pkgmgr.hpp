#pragma once
#include <string>
#include <map>
#include <vector>

struct PkgIndex {
    std::map<std::string,std::string> pkgs; // name -> path/url
    bool load(const std::string& file="pkgindex.json");
    bool save(const std::string& file="pkgindex.json") const;
    void add(const std::string& name, const std::string& src);
    void remove(const std::string& name);
    std::vector<std::string> list() const;
};

int pkg_main(int argc, char** argv);
