# 🦋 R3C --- Rust Independence Compiler

> **"No C. No LLVM. Only Rust and Assembly."**

------------------------------------------------------------------------

## 🧠 개요 (Overview)

R3C는 Rust 언어가 C나 LLVM의 의존 없이 독립적으로 자기 자신을 빌드할 수
있음을 증명하는 실험적 프로젝트다.\
Rust 코드를 직접 NASM 어셈블리로 트랜스파일하고, 별도의 런타임이나 표준
라이브러리 없이 실행 파일을 생성한다.

------------------------------------------------------------------------

## ⚙️ 구조 (Architecture)

    Rust Source (.rs)
        ↓
    R3C Frontend (C++17)
        ↓
    Token / IR 변환
        ↓
    NASM Backend
        ↓
    Assembler + Linker
        ↓
    Executable (EXE / ELF)

Frontend는 Rust 문법을 파싱하여 중간 토큰 트리를 생성하고, Backend는
NASM 명령어로 매핑한다.

------------------------------------------------------------------------

## 📁 디렉토리 구조 (Directory Structure)

  -----------------------------------------------------------------------
  Path                                설명
  ----------------------------------- -----------------------------------
  `/src/`                             핵심 C++ 소스 (`transpiler.cpp`,
                                      `pkgmgr.cpp`, `manifest.cpp`)

  `/rustlib/`                         생성된 Rust 코드 및 트랜스파일
                                      결과물

  `/docs/`                            설계 문서 및 기술 명세

  `/build/`                           CMake 빌드 산출물

  `/scripts/`                         자동화 및 배포 스크립트

  `/.github/workflows/`               자동화 워크플로우
  -----------------------------------------------------------------------

------------------------------------------------------------------------

## 🧩 주요 구성요소 (Core Components)

-   `transpiler.cpp`: Rust → NASM 변환 로직\
-   `pkgmgr.cpp`: 패키지/의존성 관리\
-   `manifest.cpp`: 프로젝트 메타데이터 파서\
-   `r3c.cpp`: 파이프라인 제어 및 CLI 엔트리

------------------------------------------------------------------------

## 🧱 빌드 방법 (Build Instructions)

``` bash
git clone https://github.com/0200134/r3c.git
cd r3c
cmake -B build -S .
cmake --build build
```

빌드 후 실행:

``` bash
./build/r3c --emit-asm --emit-asm-from-rust --asm-out build/out_lts.asm
nasm -f win64 build/out_lts.asm -o build/out_lts.obj
ld build/out_lts.obj -o build/out_lts.exe
```

------------------------------------------------------------------------

## 🤖 자동화 (Automation)

  파일                   설명
  ---------------------- ------------------------------
  `project-auto.yml`     Issue / PR 자동 보드 이동
  `weekly-summary.yml`   주간 작업 배지 자동 업데이트
  `test-build.yml`       (예정) 자동 빌드/테스트 검증

------------------------------------------------------------------------

## 🤝 기여 (Contributing)

-   브랜치 생성

    ``` bash
    git checkout -b feature/my-feature
    ```

-   `.c` 파일 금지\

-   외부 라이브러리 최소화\

-   C++17 이상 표준 사용\

-   PR 병합 시 자동으로 ✅ Done 상태로 마크됨

------------------------------------------------------------------------

## 🛣️ 로드맵 (Roadmap)

  단계      목표                                  상태
  --------- ------------------------------------- ------------
  Phase 1   Rust → NASM 트랜스파일러              ✅ 완료
  Phase 2   NASM → EXE 링크 파이프라인            🔄 진행 중
  Phase 3   Bootstrap (R3C로 R3C 빌드)            ⏳ 계획
  Phase 4   R3C-LTS 배포 및 독립 Rust 환경 구축   🚀 예정

------------------------------------------------------------------------

## 📜 라이선스 (License)

MIT License --- 자유로운 사용, 수정, 재배포 가능.

------------------------------------------------------------------------

## 💬 철학 (Manifesto)

> "C는 이제 쉬어도 된다.\
> Rust가 스스로 걸을 때다."

R3C는 Rust 생태계가 스스로 서는 순간을 준비하는 실험이다.\
C 없이, LLVM 없이, 오직 Rust와 어셈블리만으로.
