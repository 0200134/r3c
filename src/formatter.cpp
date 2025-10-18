#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include "pkgmgr.hpp"

using namespace std;
namespace fs = std::filesystem;

int run_pipeline(const vector<string>&,const string&,bool,bool,const string&,bool);
int pkg_main(int argc, char** argv);

// 간단 포매터/테스터/문서화 선언
int fmt_main();
int test_main();
int doc_main();

int main(int argc,char** argv){
    if(argc>1){
        string cmd=argv[1];
        if(cmd=="pkg") return pkg_main(argc-1,argv+1);
        if(cmd=="fmt") return fmt_main();
        if(cmd=="test") return test_main();
        if(cmd=="doc") return doc_main();
        if(cmd=="build"||cmd=="run"||cmd=="clean"){
            if(cmd=="clean"){ fs::remove_all("build"); cout<<"[OK] cleaned\n"; return 0; }
            vector<string> args;
            return run_pipeline(args,"",true,false,"build/out_lts.asm",true);
        }
    }
    // default: 대화형 파이프라인
    vector<string> args;
    return run_pipeline(args,"",true,false,"build/out_lts.asm",true);
}
