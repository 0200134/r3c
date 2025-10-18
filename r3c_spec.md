 아래는 Rust 3.0 (R3C) 공식 사양 초안 v0.1 —




# R3 Specification (Draft v0.1)
**Project:** R3C (Rust 3.0 Compiler)  
**Author:** 0200134  
**License:** MIT  
**Status:** Draft  
**Last Updated:** 2025-10-18  

---

## 1. Abstract
R3 (Rust 3.0)는 기존 Rust 언어의 LLVM 의존성을 제거하고,  
Rust 자체로부터 완전한 독립형 컴파일 파이프라인을 구축하기 위한 프로젝트이다.  

R3C는 Rust 3.0 사양을 정의하며, 다음을 목표로 한다:
- LLVM / C 없이 직접 NASM으로 코드 생성
- 안정적인 ABI 및 Self-Bootstrap 가능 구조
- 산업용(LTS) Rust 생태계의 기반 제공

---

## 2. Motivation
Rust는 안전성과 현대적 언어 구조를 제공하지만,  
여전히 **LLVM에 의존**하여 완전한 독립을 이루지 못했다.  

R3의 목표는 다음과 같다:
- Rust 코드를 자체 파서 및 코드젠으로 처리
- `R3C -> NASM -> Binary` 단계를 통한 완전한 독립 빌드
- 안정적인 ABI 및 리플렉션 구조를 도입하여 산업 장기 지원 버전(R3LTS)을 제공

---

## 3. Architecture Overview

### 3.1 Pipeline Flow



[R3 Source]
↓
[Transpiler]  (C++ 기반 초기부트)
↓
[NASM Generator]
↓
[Assembler / Linker]
↓
[Executable Binary]



### 3.2 Components
| 모듈 | 설명 |
|------|------|
| `transpiler.cpp` | Rust → NASM 변환기 |
| `stdlib.cpp` | 기본 런타임 제공 |
| `r3clib.rs` | Rust 3.0 표준 코어 라이브러리 |
| `r3c_spec.md` | Rust 3.0 공식 사양 |

### 3.3 Bootstrap
- 초기 단계는 C++을 이용하여 `r3c`를 빌드한다.  
- 이후 R3 자체를 이용해 R3를 다시 빌드(Self-Host).  
- 목표: “C 없이 Rust가 Rust를 빌드하는 구조”

---

## 4. Syntax Specification

### 4.1 차이점 (Compared to Rust 1.x/2.x)
| 구분 | Rust 1.x/2.x | R3 |
|------|---------------|----|
| 코드 생성 | LLVM | NASM 직접 출력 |
| ABI | 비공식 | 명시적, 안정적 |
| 모듈 구조 | crate 기반 | crate + unit |
| unsafe | 런타임 제한적 | 정적 경고 + 명시적 서명 |
| 리플렉션 | 불가 | 컴파일 타임 메타정보 가능 |

### 4.2 문법 확장
```rust
#[reflect] fn meta() { ... }
#[naked] fn raw_call() { asm!("mov rax, 1"); }
#[unit("core")] mod core { ... }




5. Type System & Memory Model


5.1 Type Rules




&T : 불변 참조


&mut T : 가변 참조 (unique)


~T : 소유권 이전형 (move semantics)


@T : 정적 전역 참조형 (R3 확장)




5.2 Memory Model




명시적 스택 프레임 관리


NASM 기반 레지스터 매핑 (RAX, RBX, RCX 등)


호출 규약: R3-ABI v1





6. Codegen & NASM Pipeline


6.1 규칙 요약




Rust 표현
NASM 출력




let a = 1;
mov rax, 1


a + b
add rax, rbx


if cond {}
cmp eax, 0; jne ...


while {}
jmp loop_start




6.2 호출 규약 (R3-ABI v1)




인자 전달: RCX, RDX, R8, R9


반환: RAX


스택 정렬: 16바이트 단위


프롤로그/에필로그 자동 삽입





7. Standard Library Core


7.1 최소 구현


pub fn print(msg: &str) { /* syscall write */ }
pub fn panic(msg: &str) -> ! { /* syscall exit */ }
pub fn alloc(size: usize) -> *mut u8 { /* heap stub */ }



7.2 런타임 파일 구조


r3clib/
 ├── core.rs
 ├── io.rs
 ├── mem.rs
 └── syscall.rs




8. Self-Bootstrap Flow




cmake -B build -S .


cmake --build build


.\build\r3c.exe --emit-asm --asm-out out.asm


nasm -f win64 out.asm -o out.obj


link out.obj /SUBSYSTEM:CONSOLE


(이후 단계) r3c 자체로 r3c.rs 빌드





9. Future Work




R3LTS (Long-Term Stable Rust)



ABI 안정 버전


리플렉션 API


메타데이터 내장 ELF 지원






Bare-metal / Embedded 지원



NASM 기반 부트 코드 생성


ARM64, RISC-V 백엔드 확장






Rust → R3 자동 변환기



기존 rustc 호환 코드 변환









10. Appendix


10.1 예제: R3 → NASM


fn main() {
    let a = 10;
    let b = 20;
    print("Sum: ");
    print(a + b);
}



→ Generated NASM:


mov rax, 10
mov rbx, 20
add rax, rbx
call print




R3C Motto:




“No LLVM, No Borrow Checker Overhead — Just Rust, from Rust.”





---




