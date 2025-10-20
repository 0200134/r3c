src/transpiler.cpp (A+B+C 통합 완전판)


#define _HAS_STD_BYTE 0
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include "transpiler.hpp"
#include <fstream>
#include <regex>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <map>
#include <vector>
#include <stack>
#include <thread>
#include <cctype>
#include <optional>

using namespace std;
namespace fs = std::filesystem;

#ifdef _WIN32
#include <windows.h>
#endif

// ========== logging ==========
static void enable_vt_colors() {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h != INVALID_HANDLE_VALUE) {
        DWORD m = 0;
        if (GetConsoleMode(h, &m)) SetConsoleMode(h, m | 0x0004);
    }
#endif
}
static void log_info(const char*m){cout<<"\x1b[36m[INFO]\x1b[0m "<<m<<"\n";}
static void log_ok(const char*m){cout<<"\x1b[32m[OK]\x1b[0m "<<m<<"\n";}
static void log_step(const char*m){cout<<"\x1b[35m[STEP]\x1b[0m "<<m<<"\n";}
static void log_err(const char*m){cerr<<"\x1b[31m[ERR]\x1b[0m "<<m<<"\n";}
static void log_cmd(const string&s){cout<<"\x1b[33m[CMD]\x1b[0m "<<s<<"\n";}
static void log_run(const string&s){cout<<"\x1b[33m[RUN]\x1b[0m "<<s<<"\n";}

// ========== helpers ==========
static inline string trim(string s){
    size_t i=0,j=s.size();
    while(i<j && isspace((unsigned char)s[i])) ++i;
    while(j>i && isspace((unsigned char)s[j-1])) --j;
    return s.substr(i,j-i);
}
static string unescape(const string&s){
    string o; o.reserve(s.size());
    for(size_t i=0;i<s.size();++i){
        if(s[i]=='\\'&&i+1<s.size()){
            char c=s[++i];
            if(c=='n')o+='\n'; else if(c=='t')o+='\t'; else o+=c;
        }else o+=s[i];
    }
    return o;
}
static bool is_number(const string& t){
    if(t.empty()) return false;
    size_t i=0; if(t[0]=='+'||t[0]=='-') i=1;
    if(i>=t.size()) return false;
    for(;i<t.size();++i) if(!isdigit((unsigned char)t[i])) return false;
    return true;
}
static void nasm_escape_str(string& s){
    string o; o.reserve(s.size()+8);
    for(char c: s){
        if(c=='"') o += "\\\"";
        else if(c=='\n' || c=='\r') o += "\\n";
        else o += c;
    }
    s.swap(o);
}

// ========== IR ==========
struct Expr; // forward
struct Stmt {
    enum Kind {
        LET, ASSIGN, PRINT, RUN, RUN_SH,
        IF_EQ, IF_NE, ELSE, END,
        WHILE_EQ, WHILE_NE,
        RETURN,
        EXPR_STMT,
        FN_BEGIN, FN_END
    } kind;
    string a,b,c;           // generic (ids/immediates)
    string fmt;             // for PRINT
    vector<string> args;    // for PRINT args
    unique_ptr<Expr> expr;  // for RETURN/EXPR_STMT/ASSIGN RHS
};
struct Function {
    string name;
    vector<string> params;
    vector<Stmt> body;
};
struct Program { vector<Function> fns; };

// ========== Lexer/Parser ==========
enum class TokTy { ID, NUM, STR, LPAR, RPAR, LBR, RBR, COMMA, SEMI, PLUS, MINUS, MUL, DIV, EQ, EQEQ, NE, IF, ELSE, WHILE, LET, FN, RETURN, PRINTLN, RUN_CMD, RUN_SHELL, EOFF };
struct Tok { TokTy t; string v; };

static vector<Tok> lex_all(const string& s){
    vector<Tok> out; size_t i=0, n=s.size();
    auto isid=[&](char c){ return isalnum((unsigned char)c)||c=='_'; };
    while(i<n){ char c=s[i];
        if(isspace((unsigned char)c)){ ++i; continue; }
        if(isalpha((unsigned char)c)||c=='_'){
            size_t j=i+1; while(j<n && isid(s[j])) ++j; string w=s.substr(i,j-i); i=j;
            if(w=="let") out.push_back({TokTy::LET,w});
            else if(w=="if") out.push_back({TokTy::IF,w});
            else if(w=="else") out.push_back({TokTy::ELSE,w});
            else if(w=="while") out.push_back({TokTy::WHILE,w});
            else if(w=="fn") out.push_back({TokTy::FN,w});
            else if(w=="return") out.push_back({TokTy::RETURN,w});
            else if(w=="println") out.push_back({TokTy::PRINTLN,w});
            else if(w=="run_cmd") out.push_back({TokTy::RUN_CMD,w});
            else if(w=="run_shell") out.push_back({TokTy::RUN_SHELL,w});
            else out.push_back({TokTy::ID,w});
        } else if(isdigit((unsigned char)c) || ((c=='-'||c=='+') && i+1<n && isdigit((unsigned char)s[i+1]))){
            size_t j=i+1; while(j<n && isdigit((unsigned char)s[j])) ++j; out.push_back({TokTy::NUM, s.substr(i,j-i)}); i=j;
        } else {
            if(c=='(') out.push_back({TokTy::LPAR,"("}), ++i;
            else if(c==')') out.push_back({TokTy::RPAR,")"}), ++i;
            else if(c=='{') out.push_back({TokTy::LBR,"{"}), ++i;
            else if(c=='}') out.push_back({TokTy::RBR,"}"}), ++i;
            else if(c==',') out.push_back({TokTy::COMMA,","}), ++i;
            else if(c==';') out.push_back({TokTy::SEMI,";"}), ++i;
            else if(c=='+') out.push_back({TokTy::PLUS,"+"}), ++i;
            else if(c=='-') out.push_back({TokTy::MINUS,"-"}), ++i;
            else if(c=='*') out.push_back({TokTy::MUL,"*"}), ++i;
            else if(c=='/') out.push_back({TokTy::DIV,"/"}), ++i;
            else if(c=='='){ if(i+1<n && s[i+1]=='='){ out.push_back({TokTy::EQEQ,"=="}); i+=2; } else { out.push_back({TokTy::EQ,"="}); ++i; } }
            else if(c=='"'){
                size_t j=i+1; string acc; while(j<n && s[j] != '"'){ if(s[j]=='\\' && j+1<n){ acc.push_back('\\'); acc.push_back(s[j+1]); j+=2; } else { acc.push_back(s[j]); j++; } }
                if(j<n && s[j]=='"') j++; out.push_back({TokTy::STR, acc}); i=j;
            } else { ++i; }
        }
    }
    out.push_back({TokTy::EOFF, ""});
    return out;
}

struct Expr {
    enum K { IMM, VAR, CALL, BIN } k; string v; vector<unique_ptr<Expr>> args; TokTy op; };

struct Parser {
    vector<Tok> ts; size_t p=0;
    Tok& peek(){ return ts[p]; }
    Tok get(){ return ts[p++]; }
    bool eat(TokTy t){ if(peek().t==t){ p++; return true; } return false; }

    unique_ptr<Expr> primary(){
        if(peek().t==TokTy::NUM){ auto t=get(); auto e=make_unique<Expr>(); e->k=Expr::IMM; e->v=t.v; return e; }
        if(peek().t==TokTy::ID){ auto id=get().v; if(eat(TokTy::LPAR)){ auto e=make_unique<Expr>(); e->k=Expr::CALL; e->v=id; if(peek().t!=TokTy::RPAR){ for(;;){ auto a=expr(); e->args.push_back(move(a)); if(eat(TokTy::COMMA)) continue; break; } } eat(TokTy::RPAR); return e; } auto e=make_unique<Expr>(); e->k=Expr::VAR; e->v=id; return e; }
        if(eat(TokTy::LPAR)){ auto e=expr(); eat(TokTy::RPAR); return e; }
        auto e=make_unique<Expr>(); e->k=Expr::IMM; e->v="0"; return e;
    }
    int prec(TokTy t){ if(t==TokTy::MUL||t==TokTy::DIV) return 20; if(t==TokTy::PLUS||t==TokTy::MINUS) return 10; return -1; }
    unique_ptr<Expr> bin_rhs(int minp, unique_ptr<Expr> lhs){ for(;;){ TokTy op=peek().t; int p=prec(op); if(p<minp) break; get(); auto rhs=primary(); TokTy op2=peek().t; int p2=prec(op2); if(p2>p) rhs=bin_rhs(p+1, move(rhs)); auto e=make_unique<Expr>(); e->k=Expr::BIN; e->op=op; e->args.push_back(move(lhs)); e->args.push_back(move(rhs)); lhs=move(e);} return lhs; }
    unique_ptr<Expr> expr(){ auto lhs=primary(); return bin_rhs(0, move(lhs)); }

    Stmt parseStmt(){ Stmt s; s.kind=Stmt::EXPR_STMT;
        if(eat(TokTy::LET)){ if(peek().t!=TokTy::ID){} s.kind=Stmt::LET; s.a=get().v; if(!eat(TokTy::EQ)){} s.expr=expr(); eat(TokTy::SEMI); return s; }
        if(peek().t==TokTy::ID){ string id=peek().v; if(ts[p+1].t==TokTy::EQ){ get(); get(); s.kind=Stmt::ASSIGN; s.a=id; s.expr=expr(); eat(TokTy::SEMI); return s; } }
        if(eat(TokTy::PRINTLN)){ eat(TokTy::LPAR); if(peek().t==TokTy::STR){ s.kind=Stmt::PRINT; s.fmt=unescape(get().v); if(eat(TokTy::COMMA)){ for(;;){ auto e=expr(); if(e->k==Expr::VAR) s.args.push_back(e->v); else if(e->k==Expr::IMM) s.args.push_back(e->v); else s.args.push_back("0"); if(eat(TokTy::COMMA)) continue; break; } } eat(TokTy::RPAR); eat(TokTy::SEMI); return s; } }
        if(eat(TokTy::RUN_CMD)){ eat(TokTy::LPAR); if(peek().t==TokTy::STR){ s.kind=Stmt::RUN; s.a=get().v; } eat(TokTy::RPAR); eat(TokTy::SEMI); return s; }
        if(eat(TokTy::RUN_SHELL)){ eat(TokTy::LPAR); if(peek().t==TokTy::STR){ s.kind=Stmt::RUN_SH; s.a=get().v; } eat(TokTy::RPAR); eat(TokTy::SEMI); return s; }
        if(eat(TokTy::RETURN)){ s.kind=Stmt::RETURN; s.expr=expr(); eat(TokTy::SEMI); return s; }
        if(eat(TokTy::IF)){ eat(TokTy::LPAR); string var=get().v; bool eq=true; if(eat(TokTy::EQEQ)) eq=true; else if(eat(TokTy::NE)) eq=false; string imm="0"; if(peek().t==TokTy::NUM) imm=get().v; eat(TokTy::RPAR); eat(TokTy::LBR); s.kind= eq?Stmt::IF_EQ:Stmt::IF_NE; s.a=var; s.b=imm; return s; }
        if(eat(TokTy::WHILE)){ eat(TokTy::LPAR); string var=get().v; bool eq=true; if(eat(TokTy::EQEQ)) eq=true; else if(eat(TokTy::NE)) eq=false; string imm="0"; if(peek().t==TokTy::NUM) imm=get().v; eat(TokTy::RPAR); eat(TokTy::LBR); s.kind= eq?Stmt::WHILE_EQ:Stmt::WHILE_NE; s.a=var; s.b=imm; return s; }
        if(eat(TokTy::ELSE)){ eat(TokTy::LBR); s.kind=Stmt::ELSE; return s; }
        if(eat(TokTy::RBR)){ s.kind=Stmt::END; return s; }
        s.kind=Stmt::EXPR_STMT; s.expr=expr(); eat(TokTy::SEMI); return s; }

    vector<Stmt> parseBlock(){ vector<Stmt> v; for(;;){ if(peek().t==TokTy::EOFF || peek().t==TokTy::RBR) break; auto st = parseStmt(); v.push_back(move(st)); if(v.back().kind==Stmt::END) break; } return v; }

    Function parseFn(){ Function f; eat(TokTy::FN); if(peek().t==TokTy::ID) f.name=get().v; eat(TokTy::LPAR); if(peek().t!=TokTy::RPAR){ for(;;){ if(peek().t==TokTy::ID) f.params.push_back(get().v); if(eat(TokTy::COMMA)) continue; break; } } eat(TokTy::RPAR); eat(TokTy::LBR); f.body = parseBlock(); return f; }

    Program parse(const string& src){ Program pr; ts = lex_all(src); p=0; while(peek().t!=TokTy::EOFF){ if(peek().t==TokTy::FN){ auto fn = parseFn(); pr.fns.push_back(move(fn)); } else { get(); } } return pr; }
};

// ========== CodeGen ==========
struct Loc { bool isReg; string reg; int off=0; };
struct FnCtx { string name; vector<string> params; map<string,Loc> sym; int frame=0; int label_id=0; };
struct RegPool { vector<string> pool = {"rbx","rsi","rdi","r12","r13","r14","r15","r10","r11"}; vector<string> free = pool; string get(){ if(free.empty()) return ""; string r=free.back(); free.pop_back(); return r;} void put(const string& r){ if(find(free.begin(),free.end(),r)==free.end()) free.push_back(r);} };

struct CG {
    ofstream a; int str_id=0; stack<int> if_ids; stack<int> if_end_ids; stack<int> while_ids;
    string cstr(const string& raw){ string s=raw; nasm_escape_str(s); string lab="S"+to_string(str_id++); a<<"section .data\n    "<<lab<<" db \""<<s<<"\",0\n"; a<<"section .text\n"; return lab; }
    string fmtstr(string fmt){ for(size_t p=0,c=0;;){ size_t k=fmt.find("{}",p); if(k==string::npos) break; fmt.replace(k,2,"%lld"); p=k+4; if(++c>=8) break; } string lab="F"+to_string(str_id++); nasm_escape_str(fmt); a<<"section .data\n    "<<lab<<" db \""<<fmt<<"\",10,0\n"; a<<"section .text\n"; return lab; }
    int new_slot(FnCtx& fn){ fn.frame += 8; return -fn.frame; }
    Loc ensure_loc(FnCtx& fn, const string& v){ auto it=fn.sym.find(v); if(it!=fn.sym.end()) return it->second; Loc L; L.isReg=false; L.off=new_slot(fn); fn.sym[v]=L; return L; }
    void mov_to(FnCtx& fn, const Loc& dst, const string& src){ if(dst.isReg) a<<"    mov "<<dst.reg<<", "<<src<<"\n"; else a<<"    mov QWORD [rbp"<<(dst.off<0? to_string(dst.off): string("+")+to_string(dst.off))<<"], "<<src<<"\n"; }
    void mov_from(FnCtx& fn, const Loc& src, const string& dst){ if(src.isReg) a<<"    mov "<<dst<<", "<<src.reg<<"\n"; else a<<"    mov "<<dst<<", QWORD [rbp"<<(src.off<0? to_string(src.off): string("+")+to_string(src.off))<<"]\n"; }

    void gen_expr(FnCtx& fn, RegPool& regs, Expr* e){
        if(e->k==Expr::IMM){ a<<"    mov rax, "<<e->v<<"\n"; return; }
        if(e->k==Expr::VAR){ auto it=fn.sym.find(e->v); if(it==fn.sym.end()){ a<<"    xor rax,rax\n"; return; } mov_from(fn,it->second,"rax"); return; }
        if(e->k==Expr::CALL){ vector<Expr*> as; for(auto& u: e->args) as.push_back(u.get()); if(as.size()>4){ for(size_t i=as.size(); i>4; --i){ gen_expr(fn,regs,as[i-1]); a<<"    push rax\n"; } } if(as.size()>=1){ gen_expr(fn,regs,as[0]); a<<"    mov rcx, rax\n"; } if(as.size()>=2){ gen_expr(fn,regs,as[1]); a<<"    mov rdx, rax\n"; } if(as.size()>=3){ gen_expr(fn,regs,as[2]); a<<"    mov r8,  rax\n"; } if(as.size()>=4){ gen_expr(fn,regs,as[3]); a<<"    mov r9,  rax\n"; } a<<"    call "<<e->v<<"\n"; if(as.size()>4) a<<"    add rsp, "<<((as.size()-4)*8)<<"\n"; return; }
        if(e->k==Expr::BIN){ Expr* L=e->args[0].get(); Expr* R=e->args[1].get(); gen_expr(fn,regs,L); gen_expr(fn,regs,R); a<<"    mov r10, rax\n"; gen_expr(fn,regs,L); if(e->op==TokTy::PLUS) a<<"    add rax, r10\n"; else if(e->op==TokTy::MINUS) a<<"    sub rax, r10\n"; else if(e->op==TokTy::MUL){ a<<"    mov r11, r10\n    cqo\n    imul r11\n"; } else if(e->op==TokTy::DIV){ a<<"    mov r11, r10\n    cqo\n    idiv r11\n"; } return; }
    }

    void gen_printf(FnCtx& fn, RegPool&, const string& fmt, const vector<string>& args){ string flab=fmtstr(fmt); a<<"    lea rcx, [rel "<<flab<<"]\n"; size_t n=args.size(); if(n>3){ for(size_t i=n;i>3;--i){ const string&t=args[i-1]; if(is_number(t)) a<<"    mov rax, "<<t<<"\n"; else { auto it=fn.sym.find(t); if(it!=fn.sym.end()) mov_from(fn,it->second,"rax"); else a<<"    xor rax,rax\n"; } a<<"    push rax\n"; } } if(n>=1){ const string&t=args[0]; if(is_number(t)) a<<"    mov rdx, "<<t<<"\n"; else { auto it=fn.sym.find(t); if(it!=fn.sym.end()) mov_from(fn,it->second,"rdx"); else a<<"    xor rdx,rdx\n"; } } if(n>=2){ const string&t=args[1]; if(is_number(t)) a<<"    mov r8, "<<t<<"\n"; else { auto it=fn.sym.find(t); if(it!=fn.sym.end()) mov_from(fn,it->second,"r8"); else a<<"    xor r8,r8\n"; } } if(n>=3){ const string&t=args[2]; if(is_number(t)) a<<"    mov r9, "<<t<<"\n"; else { auto it=fn.sym.find(t); if(it!=fn.sym.end()) mov_from(fn,it->second,"r9"); else a<<"    xor r9,r9\n"; } } a<<"    call printf\n"; if(n>3) a<<"    add rsp, "<<((n-3)*8)<<"\n"; }

    void prologue(FnCtx& fn){ a<<fn.name<<":\n    push rbp\n    mov rbp, rsp\n"; // params -> locals (max 4)
        for(size_t i=0;i<fn.params.size() && i<4;i++){ const string& p=fn.params[i]; Loc L; L.isReg=false; L.off=new_slot(fn); if(i==0) a<<"    mov QWORD [rbp"<<L.off<<"], rcx\n"; if(i==1) a<<"    mov QWORD [rbp"<<L.off<<"], rdx\n"; if(i==2) a<<"    mov QWORD [rbp"<<L.off<<"], r8\n"; if(i==3) a<<"    mov QWORD [rbp"<<L.off<<"], r9\n"; fn.sym[p]=L; }
        int need = fn.frame; int aligned = ((need + 32 + 15)/16)*16; if(aligned<32) aligned=32; a<<"    sub rsp, "<<aligned<<"\n"; fn.frame=aligned; }
    void epilogue(){ a<<"    leave\n    ret\n"; }

    void gen_stmt(FnCtx& fn, RegPool& regs, const Stmt& s){
        switch(s.kind){
            case Stmt::LET: { Loc L=ensure_loc(fn, s.a); gen_expr(fn,regs,s.expr.get()); mov_to(fn,L,"rax"); } break;
            case Stmt::ASSIGN: { Loc L=ensure_loc(fn, s.a); gen_expr(fn,regs,s.expr.get()); mov_to(fn,L,"rax"); } break;
            case Stmt::RETURN: { gen_expr(fn,regs,s.expr.get()); epilogue(); a<<"    ret\n"; } break;
            case Stmt::PRINT: { gen_printf(fn,regs,s.fmt,s.args); } break;
            case Stmt::RUN: { string lab=cstr(s.a); a<<"    lea rcx, [rel "<<lab<<"]\n    call system\n"; } break;
            case Stmt::RUN_SH: { string cmd=string("cmd /C ")+s.a; string lab=cstr(cmd); a<<"    lea rcx, [rel "<<lab<<"]\n    call system\n"; } break;
            case Stmt::IF_EQ:
            case Stmt::IF_NE: { auto it=fn.sym.find(s.a); if(it!=fn.sym.end()) mov_from(fn,it->second,"rax"); else a<<"    xor rax,rax\n"; a<<"    cmp rax, "<<s.b<<"\n"; int id=++fn.label_id; if(s.kind==Stmt::IF_EQ) a<<"    jne .IF_ELSE_"<<id<<"\n"; else a<<"    je .IF_ELSE_"<<id<<"\n"; if_ids.push(id); } break;
            case Stmt::ELSE: { if(if_ids.empty()) break; int id=if_ids.top(); if_ids.pop(); a<<"    jmp .IF_END_"<<id<<"\n"; a<<".IF_ELSE_"<<id<<":\n"; if_end_ids.push(id); } break;
            case Stmt::END: { if(!if_end_ids.empty()){ int id=if_end_ids.top(); if_end_ids.pop(); a<<".IF_END_"<<id<<":\n"; } else if(!while_ids.empty()){ int id=while_ids.top(); while_ids.pop(); a<<"    jmp .WHILE_COND_"<<id<<"\n"; a<<".WHILE_END_"<<id<<":\n"; } } break;
            case Stmt::WHILE_EQ:
            case Stmt::WHILE_NE: { int id=++fn.label_id; while_ids.push(id); a<<".WHILE_COND_"<<id<<":\n"; auto it=fn.sym.find(s.a); if(it!=fn.sym.end()) mov_from(fn,it->second,"rax"); else a<<"    xor rax,rax\n"; a<<"    cmp rax, "<<s.b<<"\n"; if(s.kind==Stmt::WHILE_EQ) a<<"    jne .WHILE_END_"<<id<<"\n"; else a<<"    je  .WHILE_END_"<<id<<"\n"; } break;
            default: break;
        }
    }

    void gen_function(Function& f){ RegPool regs; FnCtx fn; fn.name=f.name; fn.params=f.params; if(f.name=="main") a<<"global main\n"; prologue(fn); for(auto& s: f.body) gen_stmt(fn, regs, s); a<<"    xor rax,rax\n"; epilogue(); }
};

static bool parse_program(const string& path, Program& pr){ ifstream in(path); if(!in.is_open()){ log_err("cannot open rust file"); return false; } string src((istreambuf_iterator<char>(in)), {}); in.close(); Parser P; pr = P.parse(src); if(pr.fns.empty()){ log_err("no functions parsed"); return false; } return true; }

static bool emit_program_nasm(const Program& pr, const string& asm_out, const string& lts){
#ifdef _WIN32
    fs::create_directories(fs::path(asm_out).parent_path()); ofstream a(asm_out); if(!a.is_open()){ log_err("cannot open asm_out"); return false; }
    a<<"; r3c: Rust->NASM (fn/return + expr + stack locals)\n";
    a<<"default rel\nextern printf\nextern system\nextern ExitProcess\n\n";
    a<<"section .data\n";
    { string s="LTS VERSION: "+lts+"\\n"; nasm_escape_str(s); a<<"    VERMSG db \""<<s<<"\",0\n"; }
    a<<"\nsection .text\n";
    CG cg; cg.a.swap(a);
    for(auto& f: pr.fns) cg.gen_function(const_cast<Function&>(f));
    cg.a<<"main_trailer:\n    lea rcx, [rel VERMSG]\n    call printf\n    xor ecx, ecx\n    call ExitProcess\n    ret\n";
    ofstream out; out.swap(cg.a); log_ok("NASM generated (fn/expr/stack)"); return true;
#else
    return true;
#endif
}

// ========== assemble & link (auto detect) ==========
static bool assemble_and_link(const string& asmf, const string& exef) {
#ifdef _WIN32
    string obj="build/out.obj";
    string nasm_cmd="nasm -f win64 \""+asmf+"\" -o \""+obj+"\"";
    log_cmd(nasm_cmd);
    if(system(nasm_cmd.c_str())!=0){ log_err("NASM failed"); return false; }

    bool has_link=false; {
        FILE* f=_popen("where link 2>nul","r"); if(f){ char buf[256]; if(fgets(buf,sizeof(buf),f)) has_link=true; _pclose(f);} }
    string link_cmd;
    if(has_link){ link_cmd="link /nologo /SUBSYSTEM:CONSOLE /DEFAULTLIB:msvcrt /OUT:\""+exef+"\" \""+obj+"\" kernel32.lib";
    } else { log_info("MSVC link.exe not found. Falling back to MinGW gcc linker..."); link_cmd="gcc \""+obj+"\" -o \""+exef+"\" -lkernel32 -luser32 -lmsvcrt"; }
    log_cmd(link_cmd);
    if(system(link_cmd.c_str())!=0){ log_err("Linking failed"); return false; }
    log_ok("Executable linked successfully"); return true;
#else
    return true;
#endif
}

// ========== pipeline entry ==========
int run_pipeline(const vector<string>&, const string& lts, bool, bool emit, const string& asm_out, bool){
    enable_vt_colors();
    cout<<"=====================================================\n";
    cout<<"[r3c] Rust->NASM A+B+C (fn/expr/stack) bootstrap\n";
    cout<<"=====================================================\n";

    const string rust="rustlib/r3clib.rs"; const string exe="build/out.exe";
    {
        ofstream r(rust);
        r <<
            "fn add(x, y) {\n"
            "    let t = x + y;\n"
            "    return t;\n"
            "}\n"
            "fn main() {\n"
            "    let a = 1; let b = 2; let c = add(a, b);\n"
            "    println(\"sum:{}:{}:{}\", a, b, c);\n"
            "    if (c == 3) { println(\"ok:{}\", c); } else { println(\"ng:{}\", c); }\n"
            "    let i = 0; while (i != 5) { println(\"i:{}\", i); i = i + 1; }\n"
            "    run_cmd(\"echo run_cmd ok\");\n"
            "}\n";
        r.close();
    }

    if(!emit){ log_info("no emit"); return 0; }

    Program pr; if(!parse_program(rust, pr)) return 1; if(!emit_program_nasm(pr, asm_out, lts)) return 2;
    log_step("assembling"); if(!assemble_and_link(asm_out, exe)) return 3;

    string exe_norm = exe; for(auto& c: exe_norm) if(c=='/') c='\\';
    log_run(exe_norm); string cmd="\""+exe_norm+"\""; system(cmd.c_str());

    log_ok("Pipeline completed successfully."); return 0;
}



