# 🧩 R3C Source Code Map  
> Function Index & Comments  
> Version: 0.1.0-LTS (2025-10)

---

## 📁 src/transpiler.cpp
**역할:**  
Rust 소스를 NASM 어셈블리로 트랜스파일하는 핵심 엔진.

**주요 함수:**
| 함수 | 설명 |
|------|------|
| `int transpileAll(const std::vector<std::string>& files)` | 여러 Rust 파일을 순회하며 트랜스파일 수행. |
| `int transpileFile(const std::string& path)` | 단일 파일 트랜스파일, 토큰 분석 → NASM 생성. |
| `std::string generateAsm(const ASTNode& node)` | AST 노드를 NASM 코드로 변환. |
| `void emitHeader(std::ostream& out)` | ASM 헤더 (`section .text`, `global _start`) 생성. |
| `void emitFooter(std::ostream& out)` | ASM 종료 코드 삽입 (`mov rax, 60`, `syscall`). |
| `void optimizeMovChains()` | 불필요한 MOV 제거, 간단한 peephole 최적화. |
| `void dumpTokens(const std::vector<Token>& tokens)` | 디버깅용 토큰 시각화. |
| `static std::string trimQuotes(std::string s)` | 문자열 상수 따옴표 제거. |

---

## 📁 src/r3c.cpp
**역할:**  
R3C의 메인 엔트리 포인트. 명령행 옵션 파싱, 빌드 파이프라인 제어.

**주요 함수:**
| 함수 | 설명 |
|------|------|
| `int main(int argc, char* argv[])` | 진입점, 파이프라인 전체 제어. |
| `void printBanner()` | R3C 로고 및 버전 정보 출력. |
| `void parseArgs(int argc, char** argv)` | CLI 인자 파싱. |
| `void runPipeline()` | 전체 빌드 실행 (transpile → assemble → link). |
| `void showHelp()` | 사용 가능한 옵션 및 설명 출력. |
| `void handleError(const std::string& msg)` | 오류 메시지 출력 및 종료. |

---

## 📁 src/pkgmgr.cpp
**역할:**  
R3C의 의존성/패키지 관리 시스템 (Cargo 유사).

**주요 함수:**
| 함수 | 설명 |
|------|------|
| `void initPackageManager()` | 패키지 환경 초기화. |
| `void loadManifest(const std::string& path)` | `r3c.toml` 또는 `manifest.r3` 파일 로드. |
| `void downloadDependencies()` | 필요 패키지 다운로드 및 설치. |
| `void buildPackage(const std::string& pkg)` | 지정된 패키지를 빌드 (내부적으로 transpile 호출). |
| `bool verifyIntegrity()` | 패키지 무결성 검사. |
| `void syncRegistry()` | 패키지 인덱스(레지스트리) 동기화. |

---

## 📁 src/manifest.cpp
**역할:**  
R3C 프로젝트 설정(`manifest.r3` / `r3c.toml`) 파서.

**주요 함수:**
| 함수 | 설명 |
|------|------|
| `Manifest parseManifest(const std::string& path)` | 매니페스트 파일을 구조체로 변환. |
| `void printManifest(const Manifest& m)` | 매니페스트 내용 콘솔 출력. |
| `bool validateManifest(const Manifest& m)` | 필수 필드(`name`, `version`, `build`) 유효성 검사. |
| `std::string getValue(const std::string& key)` | TOML 스타일 키 조회. |
| `std::string joinPath(const std::string& base, const std::string& rel)` | 경로 보정 함수. |

---

## 📁 src/formatter.cpp
**역할:**  
출력 포맷 정리, 컬러 로그, 오류 출력 제어.

**주요 함수:**
| 함수 | 설명 |
|------|------|
| `void logInfo(const std::string& msg)` | 일반 로그. |
| `void logWarn(const std::string& msg)` | 경고 로그 (노란색). |
| `void logError(const std::string& msg)` | 오류 메시지 (빨간색). |
| `void printTokenTree(const std::vector<Token>& tokens)` | 디버깅용 토큰 트리 출력. |
| `std::string formatTime(double seconds)` | 실행 시간 포맷. |

---

## 📁 src/docgen.cpp
**역할:**  
자동 문서 생성기 (명령행 요약, 기술 문서 출력 기능).

**주요 함수:**
| 함수 | 설명 |
|------|------|
| `void generateDocs()` | CLI 명령어 목록 및 빌드 파이프라인 자동 문서화. |
| `void exportMarkdown(const std::string& outPath)` | Markdown 문서로 내보내기. |
| `void exportPDF(const std::string& outPath)` | PDF 문서 생성 (reportlab 기반). |

---

## 📁 src/r3cpkg.cpp
**역할:**  
CLI 기반 패키지 매니저 (독립 실행).

**주요 함수:**
| 함수 | 설명 |
|------|------|
| `int main(int argc, char* argv[])` | 독립 CLI 실행 엔트리. |
| `void handleCommand(const std::string& cmd)` | 명령어(`init`, `build`, `add`, `remove`) 처리. |
| `void initProject()` | 새 R3C 프로젝트 생성. |
| `void addDependency(const std::string& name)` | 종속성 추가. |
| `void buildProject()` | 빌드 파이프라인 실행. |

---

## 📁 src/lexer.hpp / parser.hpp
**역할:**  
Rust 문법 토큰화 및 구문 트리 구축. (핵심 컴파일 전단)

**주요 함수:**
| 함수 | 설명 |
|------|------|
| `std::vector<Token> tokenize(const std::string& src)` | 토큰 리스트 생성. |
| `ASTNode parseTokens(const std::vector<Token>& tokens)` | 토큰 시퀀스를 AST로 변환. |
| `void printAST(const ASTNode& root)` | 구문 트리 시각화. |

---

## 📁 src/ast.hpp
**역할:**  
AST 노드 정의 및 관리.

**구조체 및 함수:**
| 이름 | 설명 |
|------|------|
| `struct ASTNode` | 기본 노드 구조 (타입, 자식 노드 리스트 포함). |
| `struct FnNode : ASTNode` | 함수 정의 노드. |
| `struct LetNode : ASTNode` | 변수 선언 노드. |
| `struct IfNode, WhileNode` | 제어문 노드. |
| `void freeAST(ASTNode* root)` | AST 메모리 해제. |

---

## 🧱 Architecture Summary

```
r3c.cpp
 ├─ manifest.cpp
 ├─ pkgmgr.cpp
 ├─ transpiler.cpp
 │    ├─ lexer.hpp / parser.hpp
 │    ├─ ast.hpp
 │    └─ formatter.cpp
 └─ docgen.cpp
```

---

## 🧭 다음 단계 (Phase 2 문서화 계획)

| 항목 | 목표 |
|------|------|
| 함수별 인자/반환형 타입 명시 | 각 함수의 시그니처를 문서화 |
| 코드 예제 포함 | `fn main() {}` → 어셈블리 출력 비교 |
| 빌드 플로우 다이어그램 추가 | Rust → NASM → EXE 전체 과정 시각화 |
| `r3c`와 `r3cpkg` 상호 호출 관계 | CLI → Core 호출 구조 설명 |

---

**문서 버전:** 0.1.0  
**작성자:** [@0200134](https://github.com/0200134)  
**위치:** `docs/R3C_Source_Map.md`
