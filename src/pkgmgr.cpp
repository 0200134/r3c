#include "pkgmgr.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
namespace fs = std::filesystem;

static std::string trimq(std::string s){
    if(s.size()>=2 && ((s.front()=='"'&&s.back()=='"')||(s.front()=='\''&&s.back()=='\'')))
        s=s.substr(1,s.size()-2);
    return s;
}

bool PkgIndex::load(const std::string& file){
    pkgs.clear();
    if(!fs::exists(file)) return true;
    std::ifstream in(file);
    if(!in.is_open()) return false;
    std::string k,v;
    while(in>>k>>v){ pkgs[k]=v; }
    return true;
}
bool PkgIndex::save(const std::string& file) const{
    std::ofstream out(file);
    if(!out.is_open()) return false;
    for(auto& [k,v]:pkgs) out<<k<<" "<<v<<"\n";
    return true;
}
void PkgIndex::add(const std::string& name, const std::string& src){
    fs::create_directories("pkg/"+name);
    // local:PATH 형식만 1차 지원 (git/http는 스텁)
    std::string path=src;
    if(path.rfind("local:",0)==0) path=path.substr(6);
    if(fs::exists(path)){
        if(fs::is_directory(path)) fs::copy(path,"pkg/"+name,fs::copy_options::recursive|fs::copy_options::overwrite_existing);
        else fs::copy_file(path,"pkg/"+name+"/mod.rs",fs::copy_options::overwrite_existing);
    }
    pkgs[name]=src;
    save();
    std::cout<<"[OK] added "<<name<<" -> "<<src<<"\n";
}
void PkgIndex::remove(const std::string& name){
    if(pkgs.erase(name)){
        fs::remove_all("pkg/"+name);
        save();
        std::cout<<"[OK] removed "<<name<<"\n";
    } else std::cout<<"[ERR] no such pkg\n";
}
std::vector<std::string> PkgIndex::list() const{
    std::vector<std::string> r;
    for(auto& [k,_]:pkgs) r.push_back(k);
    return r;
}

static void usage(){
    std::cout<<"pkg commands: init | add <name> <local:PATH> | remove <name> | list | install-std\n";
}
int pkg_main(int argc, char** argv){
    PkgIndex idx; idx.load();
    if(argc<2){ usage(); return 0; }
    std::string cmd=argv[1];
    if(cmd=="init"){
        fs::create_directories("pkg");
        idx.save();
        std::cout<<"[OK] pkg repo initialized\n";
    } else if(cmd=="add" && argc>=4){
        idx.add(argv[2], argv[3]);
    } else if(cmd=="remove" && argc>=3){
        idx.remove(argv[2]);
    } else if(cmd=="list"){
        for(auto&s:idx.list()) std::cout<<"- "<<s<<"\n";
    } else if(cmd=="install-std"){
        idx.add("io","local:rustlib/io.rs");
        idx.add("fs","local:rustlib/fs.rs");
        idx.add("math","local:rustlib/math.rs");
    } else usage();
    return 0;
}
