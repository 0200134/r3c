🤝 R3C Contribution Guide

Project: R3C (Rust 3.0 Industrial Compiler)
Author: 0200134
License: MIT
Status: Open Contribution Enabled
Last Updated: 2025-10-18

1️⃣ 개요 (Overview)

R3C는 Rust 3.0 Industrial LTS Compiler를 목표로 하는 오픈소스 프로젝트입니다.
누구나 자유롭게 코드, 문서, 명세, 아이디어를 기여할 수 있습니다.

🦀 “No LLVM, No Borrow Checker Overhead — Just Rust, from Rust.”

2️⃣ 기여 가능한 영역
분야	설명
🧩 Core Transpiler	Rust → C++ / NASM 파이프라인 로직 개선
⚙️ Bootstrap Runtime	Self-host 빌드 루프 및 ABI 안정성
🧠 Language Spec	Rust 3.0 문법, 타입, 메모리 모델 정의
📘 Documentation	r3c_spec.md, README, Example 추가
🧪 Tests	Rust 샘플코드 / ASM 비교 검증
🔧 Tools	빌드 스크립트, 템플릿, CI/CD 자동화
3️⃣ 저장소 구조
r3c/
 ├── src/                 # Core transpiler (C++)
 ├── rustlib/             # Rust core library (r3clib.rs)
 ├── build/               # Build output
 ├── docs/                # Specification & guides
 ├── .github/             # Issue/PR templates
 └── examples/            # Rust sample codes

4️⃣ 협업 규칙 (Workflow)
🧠 기본 원칙

main 브랜치는 보호된 브랜치입니다.
직접 push 불가, 반드시 Pull Request(PR) 로 병합됩니다.

PR은 최소 1명 이상의 승인(Review) 후 merge됩니다.

🔀 기여 절차 (Fork + PR)

저장소 Fork

로컬 클론

git clone https://github.com/<yourname>/r3c.git
cd r3c


브랜치 생성

git checkout -b feature/<기능명>


수정 후 테스트

cmake -B build -S .
cmake --build build
.\build\r3c.exe --emit-asm-from-rust --asm-out build\test.asm


커밋

git add .
git commit -m "[Feature] Add new Rust→ASM rule"


PR 생성

제목 예시: [Feature] while loop NASM emit 개선

내용: 변경 이유 + 테스트 결과 첨부

5️⃣ 코드 기준
항목	규칙
C++	C++17 이상, clang-format 스타일 준수
Rust	2021 edition, nightly 사용 금지
ASM	NASM 문법 기준
주석	한국어+영문 병기 가능
함수명	snake_case / class명은 PascalCase
빌드 스크립트	CMake 기반, OS-agnostic 권장
6️⃣ 문서 기여

기술 문서는 docs/에 추가

마크다운(Markdown) 형식 필수

코드, 다이어그램, 예제 포함 권장

명세 수정 시 r3c_spec.md에 버전/날짜/변경 이유 반드시 기록

7️⃣ 이슈 등록 규칙
타입	접두어	설명
🐛 Bug	[Bug]	빌드/트랜스파일 문제
💡 Feature	[Feature]	새 기능 제안
📘 Spec	[Spec]	명세 변경 제안
🧾 Doc	[Doc]	문서 수정/추가
8️⃣ 코드 리뷰 원칙

리뷰는 기술 정확성 + 일관성 + 안정성 기준으로 진행

리뷰어는 명세(r3c_spec.md) 기준을 우선시함

승인 후 merge는 squash 또는 rebase 방식 사용

9️⃣ 라이선스

모든 기여 코드는 MIT License 하에 병합됩니다.
기여자는 자동으로 라이선스 조항에 동의한 것으로 간주됩니다.

🔗 링크

📘 r3c_spec.md — 기술 사양

🧩 CONTRIBUTING.md — 기본 가이드

🐛 Bug Report Template
