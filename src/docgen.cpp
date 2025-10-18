#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
int doc_main(){
    namespace fs = std::filesystem;
    std::regex re(R"(///\s?(.*))");
    std::ofstream out("build/README.md");
    out<<"# r3c Docs\n\n";
    for(auto& p: fs::recursive_directory_iterator("rustlib")){
        if(p.path().extension()==".rs"){
            std::ifstream f(p.path()); std::string line; std::smatch m;
            while(std::getline(f,line)){
                if(std::regex_match(line,m,re)) out<<"- "<<m[1]<<"\n";
            }
        }
    }
    std::cout<<"[OK] docs at build/README.md\n";
    return 0;
}
