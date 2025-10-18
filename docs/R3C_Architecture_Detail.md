
# ⚙️ R3C Architecture Detail

> “The closer to metal, the closer to truth.”

---

## 🧩 1. Core Components Overview

| 파일 | 주요 역할 |
|------|------------|
| `transpiler.cpp` | Rust 문법을 분석하고 NASM 어셈블리 코드로 변환 |
| `r3c.cpp` | 메인 엔트리. 파이프라인 초기화, 옵션 파싱, 전체 빌드 실행 |
| `pkgmgr.cpp` | 패키지/의존성 관리기. `r3cpkg` CLI와 연동 |
| `manifest.cpp` | `r3c.toml` 또는 `manifest.r3` 등 프로젝트 메타데이터 파서 |
| `formatter.cpp` | 출력 정리, 문자열 트리밍, 토큰 구조 시각화 |
| `docgen.cpp` | (선택적) 자동 문서 생성 및 CLI 요약 출력기 |
| `r3cpkg.cpp` | 독립 CLI 명령어 도구. 패키지 설치, 빌드, 경로 동기화 담당 |

---

## 🔩 2. Transpilation Pipeline (Rust → NASM)

R3C의 핵심은 `transpiler.cpp` 에 있다.  
Rust 코드를 받아 다음 단계를 거쳐 NASM 어셈블리 코드로 변환한다:




[Rust Source]
↓
[Lexer / Tokenizer]
↓
[Syntax Tree Builder]
↓
[Instruction Generator]
↓
[NASM Assembly Output]



- **Lexer** : 토큰을 분리 (fn, let, while, if, else 등)
- **Parser** : 구문 트리 구성 (`AST`)
- **Emitter** : 각 구문을 NASM 명령어로 매핑  
  예:  
  ```rust
  let x = 5;



→


mov rax, 5
mov [x], rax





Optimizer (실험적) : 불필요한 MOV 제거, 레지스터 재활용





🧱 3. Build & Linking Pipeline


[R3C Output ASM]
     ↓
NASM Assembler
     ↓
Object File (.obj / .o)
     ↓
Linker (ld)
     ↓
Executable (EXE / ELF)





목표: LLVM을 전혀 거치지 않고 완전 독립적인 빌드 체인


Windows → nasm -f win64, ld


Linux → nasm -f elf64, ld -dynamic-linker /lib64/ld-linux-x86-64.so.2





🧠 4. Token System


R3C는 단순 문자열 치환이 아니라 토큰 트리 기반 변환기이다.




Token 종류
예시
설명




FN
fn main()
함수 정의 시작


LET
let a = 10
지역 변수 선언


IF/ELSE
조건 분기
Jump 및 비교 명령으로 변환


WHILE
반복문
루프 레이블 + 조건 분기로 변환


RETURN
ret 명령어로 변환






🧰 5. Command Line Options




명령어
설명




--emit-asm
NASM 어셈블리 파일 생성


--emit-asm-from-rust
Rust 코드에서 직접 변환 수행


--asm-out <path>
ASM 출력 경로 지정


--transpile-all
전체 소스 파일 트랜스파일


--run-pipeline
ASM → 오브젝트 → 실행파일 자동 빌드


--verbose
세부 로그 출력





🔧 6. Package System (r3cpkg)


r3cpkg.cpp 는 Rust의 Cargo와 유사한 패키지 관리기다.


r3cpkg init
r3cpkg add rustlib/core
r3cpkg build





manifest.r3 또는 r3c.toml 에 메타데이터 저장


빌드 시 자동 종속성 다운로드 및 경로 설정


향후 버전에서는 r3cpkg publish 로 패키지 등록 예정





🧬 7. Manifest Format


[package]
name = "r3c"
version = "0.1.0"
edition = "lts-2025"

[build]
emit = ["asm", "exe"]
output = "build/out_lts"

[dependencies]
core = "r3c/core"
std = "r3c/std"




🚦 8. Error Handling System


R3C는 가능한 한 C의 errno 스타일 대신 Rust식 결과 처리 모델을 채택했다.


Result<R3CUnit, R3CError> transpile(const std::string& path);





성공 → R3CUnit (AST + ASM 출력 정보)


실패 → R3CError (라인, 토큰, 오류 원인 포함)




예시 출력:


[ERROR] unexpected token at line 12: "fn"




🧱 9. Planned Extensions




항목
목표
상태




Struct / Union
Rust 구조체 → ASM 메모리 블록 매핑
🧩 설계 중


Type System
기본형 (i32, f64, bool) 완전 지원
✅ 완료


Pattern Match
Rust match 문 → Jump Table 변환
🚧 진행 중


Function Pointer
레지스터 간접 호출
✅ 지원


Bootstrap
R3C 자체 컴파일
⏳ 준비 중





💬 10. Design Philosophy




“The fewer the abstractions, the closer to metal.”

— R3C Manifesto




R3C는 단순한 Rust 트랜스파일러가 아니다.

Rust의 독립성과 컴파일러 구조 자체를 C/LLVM 없이 직접 증명하려는 실험 플랫폼이다.

C 언어의 정신은 유지하되, Rust의 안전성과 현대 문법을 이어받는다.



Document: docs/R3C_Architecture_Detail.md

Author: @0200134

Version: 0.1.0 LTS (2025-10)



---




