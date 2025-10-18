



# r3c_spec.md  
### Rust → NASM Transpiler + Bootstrap Pipeline

---

## 1. 개요
r3c는 Rust 코드를 NASM 어셈블리로 직접 변환하여 실행 파일을 생성하는 독립형 트랜스파일러다.  
C, LLVM, libc 없이 작동하며 CMake + NASM + MinGW만 필요하다.

- 목적: Rust의 완전한 독립 실행
- 철학: “LLVM-free, C-free, self-bootstrapping”
- 플랫폼: Windows x86_64

---

## 2. 구조




Rust Source → Transpiler → NASM Writer → nasm → gcc → Executable



- **Transpiler:** Rust 문법을 파싱하여 NASM 코드로 변환  
- **Bootstrap:** 자기 자신을 NASM으로 재컴파일 가능  
- **Runtime Stub:** 최소한의 WinAPI 호출  
- **Diagnostic:** 괄호, 함수, 변수 개수 검사  

---

## 3. 구성 요소

| 파일 | 설명 |
|------|------|
| `transpiler.cpp` | Rust → NASM 변환기 |
| `parser.cpp` | 구문 분석 |
| `nasm_writer.cpp` | 어셈블리 출력 |
| `stdlib.cpp` | 런타임 함수 (print 등) |
| `r3c.cpp` | 메인 CLI |
| `CMakeLists.txt` | 빌드 설정 |

---

## 4. 빌드

```bash
cmake -B build -S .
cmake --build build
build\r3c.exe --emit-asm --asm-out build\out.asm
nasm -f win64 build\out.asm -o build\out.obj
gcc build\out.obj -o build\out.exe




5. 트랜스파일 예시


Rust


fn main() {
    let a = 10;
    let b = 20;
    println!("{}", a + b);
}



NASM


mov rax, 10
mov rbx, 20
add rax, rbx
call print_int




6. 부트스트랩 단계




C++ 버전 r3c 빌드


transpiler.cpp를 Rust로 변환


Rust 버전으로 r3c 재빌드


NASM 어셈블로 자체 컴파일





7. 향후 계획




if/else, loop, match 구문 지원


Linux ELF 출력


IR 중간 레이어 도입


완전한 Rust 부트스트랩 (r3c-rs)





MIT License © 2025 r3c Project



---


