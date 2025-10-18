#pragma once
#include <string>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/syscall.h>
#include <unistd.h>
#endif

namespace r3c {
inline void println(const std::string& s){
#ifdef _WIN32
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD w=0; std::string t=s; t.push_back('\n');
    WriteConsoleA(h,t.c_str(),(DWORD)t.size(),&w,nullptr);
#else
    std::string t=s; t.push_back('\n');
    syscall(SYS_write, 1, t.c_str(), t.size());
#endif
}
}
