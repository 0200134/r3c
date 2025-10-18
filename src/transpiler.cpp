// transpiler.cpp — Rust→NASM(Win64) C-free
// v4.2: Diagnostics + Auto-Refactor (rule-based only; no AI)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "transpiler.hpp"

#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <filesystem>
#include <vector>
#include <set>
#include <map>
#include <optional>
#include <cctype>
#include <cstdlib>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;
namespace fs = std::filesystem;

// ---------- console helpers ----------
static void vt_on(){
#ifdef _WIN32
    DWORD m=0; HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    if(h!=INVALID_HANDLE_VALUE && GetConsoleMode(h,&m)) SetConsoleMode(h, m|0x0004);
#endif
}
static void ok (const string& s){ cout << "\x1b[32m[OK]\x1b[0m "  << s << "\n"; }
static void err(const string& s){ cerr << "\x1b[31m[ERR]\x1b[0m " << s << "\n"; }
static void step(const string& s){ cout<< "\x1b[35m[STEP]\x1b[0m " << s << "\n"; }
static void cmd (const string& s){ cout << "\x1b[33m[CMD]\x1b[0m " << s << "\n"; }
static void diag(const string& s){ cout << "[DIAG] " << s << "\n"; }
static void refa(const string& s){ cout << "\x1b[36m[REFACTOR]\x1b[0m " << s << "\n"; }

// ---------- util ----------
static inline string trim(string s){
    auto ws=[](int c){ return !!isspace((unsigned char)c); };
    while(!s.empty() && ws(s.front())) s.erase(s.begin());
    while(!s.empty() && ws(s.back()))  s.pop_back();
    return s;
}
static bool isnum(const string& s){
    if(s.empty()) return false;
    size_t i=0; if(s[0]=='+'||s[0]=='-') i=1; if(i>=s.size()) return false;
    for(; i<s.size(); ++i) if(!isdigit((unsigned char)s[i])) return false;
    return true;
}
static vector<string> split_words(const string& s){
    vector<string> out; string t;
    for(char c: s){
        if(isalnum((unsigned char)c) || c=='_' ) t.push_back(c);
        else { if(!t.empty()){ out.push_back(t); t.clear(); } }
    }
    if(!t.empty()) out.push_back(t);
    return out;
}
static string last_ident_of_use(const string& useLine){
    // use a::b::C;
    auto s = useLine;
    auto p = s.find("use ");
    if(p!=string::npos) s = s.substr(p+4);
    auto sc = s.find(';');
    if(sc!=string::npos) s = s.substr(0, sc);
    s = trim(s);
    size_t pos = s.find_last_of(':');
    if(pos!=string::npos) return trim(s.substr(pos+1));
    return s;
}

// ---------- IR ----------
struct Stmt {
    enum Kind { LET, PRINTLN, PRINT, IF_EQ, ELSE_, END, WHILE_LT, FOR_RANGE, RETURN,
                CALL, FS_EXISTS, SLEEP_MS } kind;
    string var, a, b, text;
    vector<string> args;
    int n1=0, n2=0;
    int msgIdx=-1, pmsgIdx=-1, pathIdx=-1;
};
struct Function {
    string name;
    bool is_main=false, is_test=false;
    vector<string> params;
    vector<Stmt> body;
    set<string> locals;
};
struct IR {
    vector<Function> fns;
    vector<string> d_println, d_print, d_paths, d_lits;
};

// ---------- Expr ----------
struct Expr {
    enum T { NUM, VAR, ADD, SUB, MUL, DIV } t;
    string v; Expr* L=nullptr; Expr* R=nullptr;
    explicit Expr(T t):t(t){} Expr(T t, string vv):t(t),v(std::move(vv)){}
};
static optional<long long> eval(Expr* e){
    switch(e->t){
        case Expr::NUM: return stoll(e->v);
        case Expr::VAR: return nullopt;
        case Expr::ADD:{auto L=eval(e->L),R=eval(e->R); if(L&&R) return *L+*R; return nullopt;}
        case Expr::SUB:{auto L=eval(e->L),R=eval(e->R); if(L&&R) return *L-*R; return nullopt;}
        case Expr::MUL:{auto L=eval(e->L),R=eval(e->R); if(L&&R) return *L**R; return nullopt;}
        case Expr::DIV:{auto L=eval(e->L),R=eval(e->R); if(L&&R && *R!=0) return *L / *R; return nullopt;}
    } return nullopt;
}
static Expr* parse_expr(const string& src){
    string s=trim(src);
    auto split=[&](char op){
        int d=0; for(size_t i=0;i<s.size();++i){ char c=s[i];
            if(c=='(') d++; else if(c==')') d--;
            else if(!d && c==op) return make_pair(trim(s.substr(0,i)), trim(s.substr(i+1)));
        } return make_pair(string(),string());
    };
    for(char op:{'+','-'}){ auto p=split(op); if(!p.first.empty()){ auto e=new Expr(op=='+'?Expr::ADD:Expr::SUB); e->L=parse_expr(p.first); e->R=parse_expr(p.second); return e; } }
    for(char op:{'*','/'}){ auto p=split(op); if(!p.first.empty()){ auto e=new Expr(op=='*'?Expr::MUL:Expr::DIV); e->L=parse_expr(p.first); e->R=parse_expr(p.second); return e; } }
    if(isnum(s)) return new Expr(Expr::NUM,s);
    return new Expr(Expr::VAR,s);
}
static void free_expr(Expr* e){ if(!e) return; free_expr(e->L); free_expr(e->R); delete e; }

// ---------- Parser (diagnostics) ----------
struct ParseStats {
    int cnt_fn=0, cnt_main=0, cnt_test_attr=0;
    int cnt_let=0, cnt_println=0, cnt_print=0;
    int cnt_if=0, cnt_else=0, cnt_end=0, cnt_while=0, cnt_for=0, cnt_return=0, cnt_call=0, cnt_sleep=0, cnt_fsx=0;
    int warn_no_match=0;
};

static bool parse_rust(const string& file, IR& ir, ParseStats& pst){
    ifstream in(file);
    if(!in){ err("cannot open source file: "+file); return false; }
    string all((istreambuf_iterator<char>(in)),{}); in.close();
    if(all.empty()){ err("empty file: "+file); return false; }
    if(fs::path(file).extension() != ".rs") diag("non-.rs extension (continuing)");

    stringstream ss(all); string line; smatch m;
    bool pending_test=false, in_fn=false; Function cur;

    regex re_attr_test(R"(^#\s*\[\s*(test|derive\s*\(\s*Test\s*\))\s*\]\s*$)");
    regex re_fn(R"(fn\s+(\w+)\s*\(\s*([^\)]*)\s*\)\s*(?:->\s*[\w:&\[\]]+\s*)?\{)");
    regex re_param(R"((\w+)\s*:\s*[\w:&\[\]]+)");
    regex re_end(R"(^\}\s*$)");

    regex re_let(R"(let\s+(?:mut\s+)?(\w+)\s*=\s*([^;]+)\s*;)");
    regex re_println(R"(println!\(\s*\"([^\"]*)\"\s*\)\s*;)");
    regex re_print(R"(print!\(\s*\"([^\"]*)\"\s*\)\s*;)");
    regex re_if(R"(if\s*\(?\s*([A-Za-z_]\w*)\s*==\s*([A-Za-z_]\w*)\s*\)?\s*\{)");
    regex re_else(R"(^\}\s*else\s*\{\s*$)");
    regex re_while(R"(while\s*\(?\s*([A-Za-z_]\w*)\s*<\s*([A-Za-z_]\w*)\s*\)?\s*\{)");
    regex re_for(R"(for\s+(\w+)\s+in\s*(\d+)\.\.(\d+)\s*\{)");
    regex re_return(R"(return\s+([^;]+)\s*;)");
    regex re_sleep(R"(r3std::time::sleep_ms\(\s*(\d+)\s*\)\s*;)");
    regex re_fs_exists_call(R"(r3std::fs::exists\(\s*\"([^\"]+)\"\s*\))");

    regex re_call(R"(^([A-Za-z_]\w*)\s*\(\s*(.*)\s*\)\s*;)");
    regex re_let_call(R"(let\s+(\w+)\s*=\s*([A-Za-z_]\w*)\s*\((.*)\)\s*;)");

    int brace_balance=0;
    int lineno=0;
    while(getline(ss,line)){
        ++lineno;
        string l=trim(line);
        if(l.empty()) continue;

        if(regex_match(l,m,re_attr_test)){ pending_test=true; pst.cnt_test_attr++; continue; }

        if(!in_fn && regex_match(l,m,re_fn)){
            cur=Function{}; cur.name=m[1]; cur.is_main=(cur.name=="main"); cur.is_test=pending_test;
            pending_test=false; in_fn=true;
            pst.cnt_fn++; if(cur.is_main) pst.cnt_main++;
            string plist=trim(m[2]);
            if(!plist.empty()){
                auto it=sregex_iterator(plist.begin(),plist.end(),re_param);
                auto ed=sregex_iterator();
                for(;it!=ed;++it){ string pn=(*it)[1]; cur.params.push_back(pn); cur.locals.insert(pn); }
            }
            brace_balance++; // '{'
            continue;
        }
        if(!in_fn){ pst.warn_no_match++; diag("no match (outside fn) line "+to_string(lineno)+": "+l); continue; }

        if(regex_match(l,m,re_let_call)){
            Stmt s; s.kind=Stmt::CALL; s.var=m[1]; s.text=m[2];
            string args=trim(m[3]); if(!args.empty()){ string tok; stringstream ts(args); while(getline(ts,tok,',')){ tok=trim(tok); if(!tok.empty()) s.args.push_back(tok);} }
            cur.body.push_back(s); cur.locals.insert(s.var); pst.cnt_call++; continue;
        }
        if(regex_match(l,m,re_let)){
            Stmt s; s.kind=Stmt::LET; s.var=m[1]; s.a=trim(m[2]); cur.locals.insert(s.var); pst.cnt_let++;
            smatch mx; if(regex_search(s.a,mx,re_fs_exists_call)){
                Stmt sx; sx.kind=Stmt::FS_EXISTS; sx.var=s.var; sx.text=mx[1]; sx.pathIdx=(int)ir.d_paths.size(); ir.d_paths.push_back(sx.text);
                cur.body.push_back(sx); pst.cnt_fsx++; continue;
            }
            cur.body.push_back(s); continue;
        }
        if(regex_match(l,m,re_println)){ Stmt s; s.kind=Stmt::PRINTLN; s.text=m[1]; s.msgIdx=(int)ir.d_println.size(); ir.d_println.push_back(s.text); cur.body.push_back(s); pst.cnt_println++; continue; }
        if(regex_match(l,m,re_print))  { Stmt s; s.kind=Stmt::PRINT;   s.text=m[1]; s.pmsgIdx=(int)ir.d_print.size();   ir.d_print.push_back(s.text);   cur.body.push_back(s); pst.cnt_print++; continue; }
        if(regex_match(l,m,re_if))     { Stmt s; s.kind=Stmt::IF_EQ;   s.a=m[1]; s.b=m[2]; cur.body.push_back(s); pst.cnt_if++; brace_balance++; continue; }
        if(regex_match(l,m,re_else))   { Stmt s; s.kind=Stmt::ELSE_;   cur.body.push_back(s); pst.cnt_else++; brace_balance++; continue; }
        if(regex_match(l,m,re_while))  { Stmt s; s.kind=Stmt::WHILE_LT; s.a=m[1]; s.b=m[2]; cur.body.push_back(s); pst.cnt_while++; brace_balance++; continue; }
        if(regex_match(l,m,re_for))    { Stmt s; s.kind=Stmt::FOR_RANGE; s.var=m[1]; s.n1=stoi(m[2]); s.n2=stoi(m[3]); cur.body.push_back(s); cur.locals.insert(s.var); pst.cnt_for++; brace_balance++; continue; }
        if(regex_match(l,m,re_sleep))  { Stmt s; s.kind=Stmt::SLEEP_MS; s.n1=stoi(m[1]); cur.body.push_back(s); pst.cnt_sleep++; continue; }
        if(regex_match(l,m,re_return)) { Stmt s; s.kind=Stmt::RETURN;  s.a=m[1]; cur.body.push_back(s); pst.cnt_return++; continue; }
        if(regex_match(l,m,re_call))   { Stmt s; s.kind=Stmt::CALL;    s.text=m[1]; string args=trim(m[2]); if(!args.empty()){string tok; stringstream ts(args); while(getline(ts,tok,',')){ tok=trim(tok); if(!tok.empty()) s.args.push_back(tok);} } cur.body.push_back(s); pst.cnt_call++; continue; }
        if(regex_match(l,m,re_end))    { Stmt s; s.kind=Stmt::END;     cur.body.push_back(s); pst.cnt_end++; brace_balance--; if(brace_balance==0){ in_fn=false; ir.fns.push_back(cur);} continue; }

        pst.warn_no_match++; diag("no match line "+to_string(lineno)+": "+l);
    }
    if(in_fn){ Stmt s; s.kind=Stmt::END; cur.body.push_back(s); ir.fns.push_back(cur); }
    if(brace_balance!=0) diag("brace imbalance detected: "+to_string(brace_balance));
    return !ir.fns.empty();
}

// ---------- layout ----------
struct FnLayout { map<string,int> offs; int sz=0; };
static FnLayout layout_locals(const Function& f){
    FnLayout L; int off=8;
    auto add=[&](const string& v){ if(!L.offs.count(v)){ L.offs[v]=off; off+=8; } };
    for(auto& p:f.params) add(p);
    for(auto& v:f.locals) add(v);
    L.sz=((off+15)/16)*16; return L;
}
static string fn_label(const string& n){ return "fn_"+n; }

// ---------- expr emit ----------
static void mov_rax_from_expr(ofstream& a, Expr* e, const FnLayout& L){
    auto k=eval(e); if(k){ a<<"    mov rax,"<<*k<<"\n"; return; }
    switch(e->t){
        case Expr::NUM: a<<"    mov rax,"<<e->v<<"\n"; break;
        case Expr::VAR:{ auto it=L.offs.find(e->v);
            if(it!=L.offs.end()) a<<"    mov rax,[rbp-"<<it->second<<"]\n";
            else a<<"    mov rax,[rel "<<e->v<<"]\n"; break; }
        case Expr::ADD: mov_rax_from_expr(a,e->L,L); a<<"    push rax\n"; mov_rax_from_expr(a,e->R,L); a<<"    mov rbx,rax\n"; a<<"    pop rax\n    add rax,rbx\n"; break;
        case Expr::SUB: mov_rax_from_expr(a,e->L,L); a<<"    push rax\n"; mov_rax_from_expr(a,e->R,L); a<<"    mov rbx,rax\n"; a<<"    pop rax\n    sub rax,rbx\n"; break;
        case Expr::MUL: mov_rax_from_expr(a,e->L,L); a<<"    push rax\n"; mov_rax_from_expr(a,e->R,L); a<<"    mov rbx,rax\n"; a<<"    pop rax\n    imul rax,rbx\n"; break;
        case Expr::DIV: mov_rax_from_expr(a,e->L,L); a<<"    push rax\n"; mov_rax_from_expr(a,e->R,L); a<<"    mov rcx,rax\n"; a<<"    pop rax\n"; a<<"    xor rdx,rdx\n    idiv rcx\n"; break;
    }
}

// ---------- data emit ----------
static void emit_header(ofstream& a){
    a<<"default rel\n";
    a<<"extern ExitProcess\nextern GetStdHandle\nextern WriteConsoleA\nextern Sleep\nextern GetFileAttributesA\n";
}
static void emit_data(ofstream& a, const IR& ir, bool test_mode){
    a<<"section .data\n";
    for(size_t i=0;i<ir.d_println.size();++i) a<<"msg_"<<i<<": db \""<<ir.d_println[i]<<"\",0Dh,0Ah,0\n";
    for(size_t i=0;i<ir.d_print.size();++i)   a<<"pmsg_"<<i<<": db \""<<ir.d_print[i]  <<"\",0\n";
    for(size_t i=0;i<ir.d_paths.size();++i)   a<<"path_"<<i<<": db \""<<ir.d_paths[i]  <<"\",0\n";
    for(size_t i=0;i<ir.d_lits.size();++i)    a<<"lit_"<<i<<": db \""<<ir.d_lits[i]   <<"\",0\n";
    if(test_mode){ a<<"t_hdr: db \"[TEST] \",0\n"; a<<"t_pass: db \"  PASS\",0Dh,0Ah,0\n"; }
}
static void emit_bss(ofstream& a){ a<<"section .bss\n"; }

// intern string literal
static int intern_lit(IR& ir, const string& s){ ir.d_lits.push_back(s); return (int)ir.d_lits.size()-1; }

// ---------- function emit ----------
struct Ctrl { enum T{IF,WHILE_,FOR_} t; int id; string forVar; };

static void load_arg(ofstream& a, const string& tok, const FnLayout& L, IR& ir, const string& reg){
    string t=trim(tok);
    if(t.size()>=2 && t.front()=='\"' && t.back()=='\"'){
        int idx=intern_lit(ir, t.substr(1,t.size()-2));
        a<<"    lea "<<reg<<",[rel lit_"<<idx<<"]\n"; return;
    }
    Expr* e=parse_expr(t); mov_rax_from_expr(a,e,L);
    if(reg=="rcx"||reg=="rdx"||reg=="r8"||reg=="r9") a<<"    mov "<<reg<<",rax\n";
    free_expr(e);
}

static void emit_function(ofstream& a, Function& f, IR& ir){
    FnLayout L=layout_locals(f);
    a<<fn_label(f.name)<<":\n";
    a<<"    push rbp\n    mov rbp,rsp\n";
    if(L.sz) a<<"    sub rsp,"<<L.sz<<"\n";
    static const char* preg[4] = {"rcx","rdx","r8","r9"};
    for(size_t i=0;i<f.params.size() && i<4;i++){ int off=L.offs.at(f.params[i]); a<<"    mov [rbp-"<<off<<"],"<<preg[i]<<"\n"; }

    int if_id=0, while_id=0, for_id=0;
    vector<Ctrl> cs;

    for(const auto& s: f.body){
        switch(s.kind){
            case Stmt::PRINTLN:{
                a<<"    mov rcx,-11\n    call GetStdHandle\n    mov rcx,rax\n";
                a<<"    lea rdx,[rel msg_"<<s.msgIdx<<"]\n";
                a<<"    mov r8d,"<<(int)(s.text.size()+2)<<"\n";
                a<<"    xor r9d,r9d\n    sub rsp,40\n    call WriteConsoleA\n    add rsp,40\n"; break;}
            case Stmt::PRINT:{
                a<<"    mov rcx,-11\n    call GetStdHandle\n    mov rcx,rax\n";
                a<<"    lea rdx,[rel pmsg_"<<s.pmsgIdx<<"]\n";
                a<<"    mov r8d,"<<(int)s.text.size()<<"\n";
                a<<"    xor r9d,r9d\n    sub rsp,40\n    call WriteConsoleA\n    add rsp,40\n"; break;}
            case Stmt::FS_EXISTS:{
                a<<"    lea rcx,[rel path_"<<s.pathIdx<<"]\n    call GetFileAttributesA\n";
                a<<"    cmp eax,0FFFFFFFFh\n    mov rax,0\n    je L_fsx_"<<s.pathIdx<<"\n";
                a<<"    mov rax,1\nL_fsx_"<<s.pathIdx<<":\n";
                a<<"    mov [rbp-"<<layout_locals(f).offs.at(s.var)<<"],rax\n"; break;}
            case Stmt::LET:{
                Expr* e=parse_expr(s.a); mov_rax_from_expr(a,e,L);
                a<<"    mov [rbp-"<<L.offs.at(s.var)<<"],rax\n"; free_expr(e); break;}
            case Stmt::IF_EQ:{
                int id=if_id++; cs.push_back({Ctrl::IF,id,{}});
                a<<"    mov rax,[rbp-"<<L.offs.at(s.a)<<"]\n";
                a<<"    cmp rax,[rbp-"<<L.offs.at(s.b)<<"]\n";
                a<<"    jne L_else_"<<id<<"\n"; break;}
            case Stmt::ELSE_:{
                if(!cs.empty() && cs.back().t==Ctrl::IF){
                    int id=cs.back().id; a<<"    jmp L_endif_"<<id<<"\nL_else_"<<id<<":\n";
                } break;}
            case Stmt::WHILE_LT:{
                int id=while_id++; cs.push_back({Ctrl::WHILE_,id,{}});
                a<<"L_while_cond_"<<id<<":\n";
                a<<"    mov rax,[rbp-"<<L.offs.at(s.a)<<"]\n";
                a<<"    cmp rax,[rbp-"<<L.offs.at(s.b)<<"]\n";
                a<<"    jge L_while_end_"<<id<<"\n"; break;}
            case Stmt::FOR_RANGE:{
                int id=for_id++; cs.push_back({Ctrl::FOR_,id,s.var});
                a<<"    mov rax,"<<s.n1<<"\n    mov [rbp-"<<L.offs.at(s.var)<<"],rax\n";
                a<<"L_for_cond_"<<id<<":\n";
                a<<"    mov rax,[rbp-"<<L.offs.at(s.var)<<"]\n";
                a<<"    cmp rax,"<<s.n2<<"\n";
                a<<"    jge L_for_end_"<<id<<"\n"; break;}
            case Stmt::CALL:{
                static const char* areg[4]={"rcx","rdx","r8","r9"};
                size_t ac=min<size_t>(4,s.args.size());
                for(size_t k=0;k<ac;k++) load_arg(a,s.args[k],L,ir,areg[k]);
                a<<"    call "<<fn_label(s.text)<<"\n";
                if(!s.var.empty()) a<<"    mov [rbp-"<<L.offs.at(s.var)<<"],rax\n"; break;}
            case Stmt::SLEEP_MS:{ a<<"    mov ecx,"<<s.n1<<"\n    call Sleep\n"; break;}
            case Stmt::RETURN:{ Expr* e=parse_expr(s.a); mov_rax_from_expr(a,e,L); free_expr(e);
                if(L.sz) a<<"    add rsp,"<<L.sz<<"\n"; a<<"    pop rbp\n    ret\n"; break;}
            case Stmt::END:{
                if(cs.empty()) break;
                Ctrl top=cs.back(); cs.pop_back();
                if(top.t==Ctrl::IF){ a<<"L_endif_"<<top.id<<":\n"; }
                else if(top.t==Ctrl::WHILE_){ a<<"    jmp L_while_cond_"<<top.id<<"\nL_while_end_"<<top.id<<":\n"; }
                else { a<<"    mov rax,[rbp-"<<L.offs.at(top.forVar)<<"]\n    add rax,1\n    mov [rbp-"<<L.offs.at(top.forVar)<<"],rax\n    jmp L_for_cond_"<<top.id<<"\nL_for_end_"<<top.id<<":\n"; }
                break;}
        }
    }
    if(L.sz) a<<"    add rsp,"<<L.sz<<"\n";
    a<<"    pop rbp\n    ret\n";
}

// ---------- whole emission (win64) ----------
static bool emit_win(IR& ir, ofstream& a, bool test_mode){
    emit_header(a);
    emit_data(a, ir, test_mode);
    emit_bss(a);

    a<<"section .text\n";
    for(auto& f: ir.fns) emit_function(a,f,ir);

    a<<"global main\nmain:\n    push rbp\n    mov rbp,rsp\n";
    if(test_mode){
        a<<"    mov rcx,-11\n    call GetStdHandle\n    mov rcx,rax\n";
        a<<"    lea rdx,[rel t_hdr]\n    mov r8d,8\n";
        a<<"    xor r9d,r9d\n    sub rsp,40\n    call WriteConsoleA\n    add rsp,40\n";
        for(auto& f: ir.fns){
            if(!f.is_test) continue;
            a<<"    call "<<fn_label(f.name)<<"\n";
            a<<"    mov rcx,-11\n            call GetStdHandle\n    mov rcx,rax\n";
            a<<"    lea rdx,[rel t_pass]\n    mov r8d,8\n";
            a<<"    xor r9d,r9d\n    sub rsp,40\n    call WriteConsoleA\n    add rsp,40\n";
        }
        a<<"    mov ecx,0\n    call ExitProcess\n";
    }else{
        bool has=false; for(auto& f: ir.fns) if(f.name=="main") has=true;
        if(has) a<<"    call "<<fn_label("main")<<"\n";
        a<<"    mov ecx,0\n    call ExitProcess\n";
    }
    return true;
}

// ---------- assemble/link ----------
static bool assemble(const string& asmfile, const string& exe){
    {   // entry label check
        ifstream af(asmfile);
        bool has_main=false; string ln;
        while(af && getline(af,ln)){ if(ln.find("global main")!=string::npos){ has_main=true; break; } }
        if(!has_main) diag("entry label not found in asm (global main) — continuing");
    }

    fs::create_directories("build");
    string s1 = "nasm -f win64 \"" + asmfile + "\" -o build/out.obj";
    cmd(s1);
    if(system(s1.c_str())!=0){ err("NASM fail"); return false; }
    diag("NASM OK (syntax/labels).");

    string s2 = "gcc build/out.obj -o \"" + exe + "\" -nostdlib -Wl,-e,main -lkernel32 -luser32";
    cmd(s2);
    if(system(s2.c_str())!=0){ err("link fail"); return false; }
    ok("Linked");
    return true;
}

// ---------- auto refactor (rule-based) ----------
static bool auto_refactor_rust(const string& path, string& out_path){
    ifstream in(path);
    if(!in.is_open()) return false;
    vector<string> lines; string line;
    while(getline(in,line)) lines.push_back(line);
    in.close();
    if(lines.empty()) return false;

    // A) 빈 println! 보정
    {
        regex re_empty_pl(R"(^\s*println!\s*\(\s*\)\s*;?\s*$)");
        for(string& l: lines){
            if(regex_match(l, re_empty_pl)){
                refa("println!() → println!(\"Debug\");");
                l = "    println!(\"Debug\"); // [auto]";
            }
        }
    }

    // B) brace balance
    int bal=0;
    for(const string& l: lines){ for(char c: l){ if(c=='{') ++bal; else if(c=='}') --bal; } }
    if(bal>0){ for(int i=0;i<bal;i++){ lines.push_back("} // [auto inserted]"); } refa("missing '}' fixed (+ "+to_string(bal)+")"); }

    // C) main return 0
    {
        int main_start=-1; int last_nonblank=(int)lines.size()-1;
        regex re_fn_main(R"(^\s*fn\s+main\s*\()");
        for(int i=0;i<(int)lines.size();++i) if(regex_search(lines[i], re_fn_main)){ main_start=i; break; }
        for(int i=(int)lines.size()-1;i>=0;--i){ if(trim(lines[i]).size()){ last_nonblank=i; break; } }
        if(main_start>=0){
            bool has_return=false;
            for(int j=main_start+1;j<=last_nonblank;++j){
                if(lines[j].find("return")!=string::npos){ has_return=true; break; }
            }
            if(!has_return){
                lines.insert(lines.begin()+last_nonblank, "    return 0; // [auto]");
                refa("added 'return 0;' into main()");
            }
        }
    }

    // D) Dead code (let unused) — 단순 토큰 스캔
    {
        // 수집: 모든 단어 토큰
        vector<string> allTokens;
        for(const auto& l: lines){
            auto ws = trim(l);
            if(ws.rfind("let ",0)==0) continue; // 선언 라인은 검사에서 제외(사용 탐색만)
            auto w = split_words(l);
            allTokens.insert(allTokens.end(), w.begin(), w.end());
        }
        // let 변수 라인에 대해 사용 여부 확인
        regex re_let(R"(^\s*let\s+(?:mut\s+)?(\w+)\s*=)");
        for(string& l: lines){
            smatch m;
            if(regex_search(l,m,re_let)){
                string v = m[1];
                bool used = false;
                for(const auto& t: allTokens){ if(t==v){ used=true; break; } }
                if(!used){
                    refa("unused variable: "+v);
                    l = "// unused variable: " + v + "\n// " + l;
                }
            }
        }
    }

    // E) 미사용 use 정리 (use ...; 의 마지막 식별자가 등장하지 않으면 주석)
    {
        // 파일 전체 토큰
        vector<string> tokens;
        for(const auto& l: lines){
            auto w = split_words(l);
            tokens.insert(tokens.end(), w.begin(), w.end());
        }
        regex re_use(R"(^\s*use\s+.+;\s*$)");
        for(string& l: lines){
            if(regex_match(l, re_use)){
                string id = last_ident_of_use(l);
                if(!id.empty()){
                    bool used=false;
                    for(const auto& t: tokens){ if(t==id){ used=true; break; } }
                    if(!used){
                        refa("unused use: " + id);
                        l = "// unused use: " + id + "\n// " + l;
                    }
                }
            }
        }
    }

    // F) 간단 들여쓰기/공백 정규화 (4 spaces), 빈 줄 압축
    {
        // collapse multiple blank lines
        vector<string> norm; norm.reserve(lines.size());
        int blank_run=0;
        for(auto& l: lines){
            if(trim(l).empty()){ blank_run++; if(blank_run>1) continue; }
            else blank_run=0;
            norm.push_back(l);
        }
        // re-indent by brace heuristic
        int depth=0; vector<string> out; out.reserve(norm.size());
        for(string l: norm){
            string t=trim(l);
            if(!t.empty() && t[0]=='}') depth=max(0,depth-1);
            if(!t.empty()) out.push_back(string(depth*4,' ') + t);
            else out.push_back("");
            if(!t.empty() && t.back()=='{') depth++;
        }
        lines.swap(out);
        refa("normalized indentation");
    }

    // G) 함수 자동 도큐 (///) — 문서가 없으면 간단 주석 삽입
    {
        regex re_fn(R"(^\s*fn\s+(\w+)\s*\()");
        for(size_t i=0;i<lines.size();++i){
            smatch m; if(regex_search(lines[i], m, re_fn)){
                if(i==0 || lines[i-1].rfind("///",0)!=0){
                    string nm = m[1];
                    lines.insert(lines.begin()+i, "/// AutoDoc: function " + nm);
                    refa("insert autodoc for fn " + nm);
                    ++i;
                }
            }
        }
    }

    // backup
    {
        string bak = path + ".bak";
        ofstream b(bak); if(b.is_open()){ for(auto& s: lines) b<<s<<"\n"; b.close(); ok("Backup saved: "+bak); }
    }

    // write refactored
    out_path = path + ".refactored.rs";
    ofstream out(out_path);
    if(!out.is_open()) return false;
    for(auto& s: lines) out<<s<<"\n";
    out.close();
    ok("Refactored file saved: " + out_path);
    return true;
}

// ---------- pipeline entry ----------
int run_pipeline(const vector<string>& /*argv*/,
                 const string& /*rust_src_cli*/,
                 bool /*emit_asm*/,
                 bool /*emit_asm_from_rust*/,
                 const string& asmout,
                 bool /*quiet*/)
{
    vt_on();
    cout<<"=====================================================\n";
    cout<<"[r3c] Rust LTS transpiler + NASM bootstrap pipeline\n";
    cout<<"=====================================================\n";

    string target; cout<<"Target? (win/linux) [win]: "; getline(cin,target); if(target.empty()) target="win";
    if(target!="win"){ err("linux backend not implemented"); return 2; }

    string mode; cout<<"Mode? (run/test) [run]: "; getline(cin,mode); if(mode.empty()) mode="run";
    bool test_mode=(mode=="test");

    string rf; cout<<"Enter Rust source file path: "; getline(cin,rf); rf=trim(rf);
    if(rf.empty()){ err("no file"); return 1; }
    if(!fs::exists(rf)){ err("not found: "+rf); return 1; }
    diag("Rust file check: OK ("+rf+")");

    // auto-refactor (always-on)
    {
        string out_rf;
        if(auto_refactor_rust(rf, out_rf)){
            rf = out_rf;
        }
    }

    step("Parsing Rust file: " + rf);
    IR ir; ParseStats pst{};
    if(!parse_rust(rf, ir, pst)){ err("parse fail"); return 1; }

    diag("fn="+to_string(pst.cnt_fn)+", main="+to_string(pst.cnt_main)+", test_attr="+to_string(pst.cnt_test_attr));
    diag("let="+to_string(pst.cnt_let)+", println="+to_string(pst.cnt_println)+", print="+to_string(pst.cnt_print));
    diag("if="+to_string(pst.cnt_if)+", else="+to_string(pst.cnt_else)+", end="+to_string(pst.cnt_end));
    diag("while="+to_string(pst.cnt_while)+", for="+to_string(pst.cnt_for)+", return="+to_string(pst.cnt_return));
    diag("call="+to_string(pst.cnt_call)+", sleep="+to_string(pst.cnt_sleep)+", fs.exists="+to_string(pst.cnt_fsx));
    if(pst.warn_no_match>0) diag("no-match lines="+to_string(pst.warn_no_match)+" (tolerated)");

    ofstream asmf(asmout, ios::binary);
    if(!asmf){ err("asm open fail"); return 2; }
    emit_win(ir, asmf, test_mode);
    asmf.close(); ok("NASM emitted");

    step("assembling");
    if(!assemble(asmout, "build/out.exe")) return 3;

    ok("Pipeline completed successfully.");
    return 0;
}
