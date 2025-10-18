#pragma once
#include <string>
#include <map>

struct Manifest {
    std::string name="app";
    std::string version="0.1.0";
    std::string target="win"; // win/linux
    std::map<std::string,std::string> deps; // name -> location (local: or git:)
};

bool load_manifest(const std::string& path, Manifest& out, std::string& err);
