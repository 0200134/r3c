# 🔗 R3C Linking Pipeline Specification  
> Phase 2 — NASM → Object → Executable  
> Version 0.2.0 (LTS 2025-10)

---

## 🧠 목적
R3C Phase 2의 목표는 **Rust → NASM으로 변환된 ASM 코드를 실제 실행 가능한 바이너리로 링크**하는 것이다.  
이 단계에서는 C 런타임(`crt0`), LLVM, libc 없이 완전한 독립 링크 체인을 구성한다.

---

## ⚙️ 파이프라인 개요

```
[Rust Source]
    ↓
Transpiler (C++)
    ↓
[.asm]  (NASM)
    ↓
Assembler → [.obj / .o]
    ↓
Linker → [.exe / .elf]
    ↓
Runnable Binary
```

---

## 🧩 단계별 설명

### 1️⃣ NASM 어셈블리 생성
- 이미 Phase 1에서 완료된 `transpiler.cpp`가 수행.  
- 생성 규칙:
  - `_start:` 엔트리 레이블 필수  
  - `section .text`, `section .data` 구분  
  - Windows: `global main`, Linux: `global _start`

---

### 2️⃣ 어셈블러 (Assembler)
| 대상 | 명령 | 출력 |
|------|------|------|
| **Windows** | `nasm -f win64 build/out.asm -o build/out.obj` | PE OBJ |
| **Linux** | `nasm -f elf64 build/out.asm -o build/out.o` | ELF OBJ |

필요 시 추가 옵션:
```bash
nasm -DDEBUG -f elf64 -g -F dwarf
```

---

### 3️⃣ 링커 (Linker)
| OS | 명령 | 출력 |
|----|------|------|
| **Windows** | `lld-link /subsystem:console build/out.obj /out:build/out.exe` | `.exe` |
| **Linux** | `ld build/out.o -o build/out.elf` | `.elf` |

링커는 R3C에서 직접 호출하거나, CLI 옵션으로 외부 링크 지정 가능:

```bash
r3c --link --target win64
r3c --link --target linux64
```

---

## 🔧 내부 구조 설계 (linker.cpp)

```cpp
// src/linker.cpp
int linkObject(const std::string& objPath, const std::string& output, const std::string& target) {
    if (target == "win64")
        return system(("lld-link /subsystem:console " + objPath + " /out:" + output).c_str());
    if (target == "linux64")
        return system(("ld " + objPath + " -o " + output).c_str());
    std::cerr << "Unsupported target\n";
    return 1;
}
```

- **입력:** `.obj` 또는 `.o`  
- **출력:** `.exe` 또는 `.elf`  
- **에러 처리:** 링크 실패 시 상세 로그 출력  

---

## 🧱 실행 예시

```bash
# 1. 트랜스파일
r3c --emit-asm --asm-out build/out.asm

# 2. 어셈블
nasm -f win64 build/out.asm -o build/out.obj

# 3. 링크
r3c --link --target win64

# 4. 실행
./build/out.exe
```

---

## 🧩 링커 옵션 설계안

| 옵션 | 설명 |
|------|------|
| `--link` | ASM → EXE 자동 링크 |
| `--link-only` | 기존 .obj를 재사용해 링크만 수행 |
| `--target <arch>` | `win64`, `linux64`, `arm64` 등 지정 |
| `--no-entry` | `_start` 없이 라이브러리 모드 컴파일 |
| `--strip` | 심볼 테이블 제거, 바이너리 최소화 |

---

## 🧠 향후 확장 계획

| 기능 | 설명 | 상태 |
|------|------|------|
| `R3C Linker (LIBR3C)` | 독자적 링커 구현 (PE/ELF 파서 내장) | 🧩 설계 중 |
| `Cross Target Build` | Win → Linux / Linux → Win 교차 컴파일 | 🚧 예정 |
| `Dynamic Section Builder` | ELF `.dynamic` 섹션 직접 생성 | 🧪 실험 단계 |
| `Bare-metal output` | OS 없는 raw bin 출력 (`nasm -f bin`) | ⏳ 후속 연구 |

---

## 🧰 내부 호출 흐름

```
main() in r3c.cpp
 ├── transpileAll()
 ├── assembleObject()
 └── linkObject()
```

---

## 🧠 설계 원칙

> “링커는 단순해야 한다.  
> 파일을 잇는 것이 아니라, 언어의 독립성을 잇는 것이다.”

R3C는 링커를 단순한 시스템 도구가 아닌 **Rust 독립성의 마지막 단계**로 정의한다.  
LLVM, libc, CRT 없이 Rust 코드를 직접 실행 가능한 바이너리로 연결한다.

---

**문서 버전:** 0.2.0  
**작성자:** [@0200134](https://github.com/0200134)  
**위치:** `docs/R3C_Linking_Pipeline.md`
