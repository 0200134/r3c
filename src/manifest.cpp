#include "manifest.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

static std::string trim(std::string s){
    auto ws = [](int c){return !!isspace(c);};
    while(!s.empty() && ws(s.front())) s.erase(s.begin());
    while(!s.empty() && ws(s.back())) s.pop_back();
    return s;
}

bool load_manifest(const std::string& path, Manifest& out, std::string& err){
    std::ifstream in(path);
    if(!in.is_open()){ err="cannot open "+path; return false; }
    std::string line, sec;
    while(std::getline(in,line)){
        line=trim(line);
        if(line.empty()||line[0]=='#') continue;
        if(line.front()=='[' && line.back()==']'){ sec=line.substr(1,line.size()-2); continue; }
        auto p=line.find('=');
        if(p==std::string::npos) continue;
        std::string k=trim(line.substr(0,p));
        std::string v=trim(line.substr(p+1));
        if(!v.empty() && (v.front()=='\"'&&v.back()=='\"')) v=v.substr(1,v.size()-2);
        if(sec=="package"){
            if(k=="name") out.name=v;
            else if(k=="version") out.version=v;
            else if(k=="target") out.target=v;
        }else if(sec=="dependencies"){
            out.deps[k]=v;
        }
    }
    return true;
}
