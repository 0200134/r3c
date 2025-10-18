// r3cpkg.cpp (요약)
#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

struct PkgManager {
    map<string,string> index;
    string file="pkgindex.json";

    void load(){
        if(fs::exists(file)){
            ifstream f(file);
            json j; f>>j;
            for(auto& [k,v]:j.items()) index[k]=v.get<string>();
        }
    }
    void save(){
        json j; for(auto& [k,v]:index) j[k]=v;
        ofstream f(file); f<<j.dump(2);
    }

    void add(const string& name, const string& path){
        index[name]=path;
        fs::create_directories("pkg/"+name);
        if(fs::exists(path)) fs::copy(path, "pkg/"+name, fs::copy_options::recursive);
        cout << "[OK] added pkg: " << name << " -> " << path << "\n";
        save();
    }

    void remove(const string& name){
        if(index.erase(name)){
            fs::remove_all("pkg/"+name);
            cout << "[OK] removed " << name << "\n";
        } else cout << "[ERR] no such pkg\n";
        save();
    }

    void list(){
        cout << "=== Installed Packages ===\n";
        for(auto& [k,v]:index)
            cout << "- " << k << " ("<<v<<")\n";
    }

    void install_std(){
        add("io",   "rustlib/io.rs");
        add("fs",   "rustlib/fs.rs");
        add("math", "rustlib/math.rs");
    }
};

int pkg_main(int argc, char** argv){
    PkgManager pm; pm.load();
    if(argc<2){ cout<<"pkg commands: add, remove, list, install-std\n"; return 0; }

    string cmd=argv[1];
    if(cmd=="add" && argc>=4) pm.add(argv[2], argv[3]);
    else if(cmd=="remove" && argc>=3) pm.remove(argv[2]);
    else if(cmd=="list") pm.list();
    else if(cmd=="install-std") pm.install_std();
    else cout<<"Unknown pkg command\n";
    return 0;
}
