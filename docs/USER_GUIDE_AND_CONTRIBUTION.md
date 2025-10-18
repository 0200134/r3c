# 👥 R3C 사용자 및 기여자 친화 환경 구축  
> Phase 3 — Accessibility & Developer Experience (DX) 강화  
> _Make R3C usable, buildable, and contributable._

---

## 🎯 목표

1. **초보자도 5분 안에 빌드 가능**  
2. **기여자가 10분 안에 PR 제출 가능**  
3. **문서/빌드/테스트 절차가 한눈에 보이게 통합**

---

## 🧩 1️⃣ 프로젝트 구조 명확화

```
r3c/
 ├── src/                  # C++ Core Source
 │   ├── transpiler.cpp
 │   ├── pkgmgr.cpp
 │   ├── manifest.cpp
 │   └── ...
 ├── docs/                 # 문서 (설명서, 로드맵 등)
 │   ├── R3C_Documentation.md
 │   ├── R3C_Source_Map.md
 │   ├── R3C_Linking_Pipeline.md
 │   └── ROADMAP_NEXT.md
 ├── build/                # 빌드 결과물
 ├── rustlib/              # Rust 샘플 코드
 ├── .github/workflows/    # 자동화 스크립트
 └── CMakeLists.txt
```

**핵심 규칙:**  
- CMake로만 빌드 (Makefile, manual compile 금지)  
- 모든 산출물은 `build/` 내부에 저장  
- 문서는 반드시 `docs/` 하위에 둔다  

---

## ⚙️ 2️⃣ 설치 및 빌드 절차 (Windows / Linux)

### 🪟 Windows
```bash
git clone https://github.com/0200134/r3c.git
cd r3c
cmake -B build -S .
cmake --build build --config Release
.uild3c.exe --emit-asm --asm-out build\out.asm
```

### 🐧 Linux
```bash
git clone https://github.com/0200134/r3c.git
cd r3c
sudo apt install cmake nasm -y
cmake -B build -S .
cmake --build build -j4
./build/r3c --emit-asm --asm-out build/out.asm
```

✅ **빌드 성공 시:**  
`build/r3c` 또는 `build/r3c.exe` 생성됨.

---

## 🧰 3️⃣ CLI 명령어 요약

| 명령 | 설명 |
|------|------|
| `--emit-asm` | Rust → NASM 변환 |
| `--link` | `.obj` → `.exe` 링크 수행 |
| `--target <arch>` | `win64`, `linux64`, `arm64` 지정 |
| `--verbose` | 상세 로그 출력 |
| `--transpile-all <src>` | 전체 디렉토리 변환 실행 |

---

## 🧑‍💻 4️⃣ 기여 절차 (Contributing)

1. 포크(Fork) 후 새 브랜치 생성  
   ```bash
   git checkout -b feature/my-feature
   ```
2. 코드 수정 → 로컬 빌드 테스트  
   ```bash
   cmake -B build -S . && cmake --build build
   ```
3. 테스트 통과 후 PR 생성  
   - PR 제목: `[scope]: description`  
   - 예시: `[transpiler]: add match expression support`
4. CI 자동 빌드 통과 시 자동 merge 후보로 전환됨.

---

## 🧾 5️⃣ ISSUE / PR 템플릿 가이드

### 📄 버그 리포트 템플릿 (`.github/ISSUE_TEMPLATE/bug_report.yml`)
```yaml
name: "🐛 Bug Report"
description: "예상치 못한 동작이나 빌드 오류를 보고합니다."
body:
  - type: input
    attributes:
      label: "환경 정보"
      description: "OS, 컴파일러 버전, 빌드 옵션 등"
  - type: textarea
    attributes:
      label: "문제 설명"
  - type: textarea
    attributes:
      label: "재현 단계"
```

### 🔀 Pull Request 템플릿 (`.github/PULL_REQUEST_TEMPLATE.md`)
```md
## ✨ 변경 내용
- 

## ✅ 체크리스트
- [ ] 빌드 및 실행 확인
- [ ] 문서 업데이트 완료
- [ ] 다른 기능과 충돌 없음
```

---

## 📚 6️⃣ 문서 접근성 강화

| 항목 | 경로 | 설명 |
|------|------|------|
| 프로젝트 개요 | `README.md` | 개념 및 철학 |
| 기술 상세 | `docs/R3C_Documentation.md` | 전체 구조 |
| 함수/클래스 맵 | `docs/R3C_Source_Map.md` | 함수 기반 문서 |
| 링크 파이프라인 | `docs/R3C_Linking_Pipeline.md` | Phase 2 설계 |
| 자동화 계획 | `docs/ROADMAP_NEXT.md` | 향후 계획 |

---

## 🧠 7️⃣ 추천 자동화 워크플로우

| 이름 | 기능 | 파일 경로 |
|------|------|-----------|
| Build Test | main 브랜치 빌드 자동 검증 | `.github/workflows/test-build.yml` |
| Project Auto | 이슈/PR 자동 보드 이동 | `.github/workflows/project-auto.yml` |
| Weekly Summary | 주간 기여 통계 갱신 | `.github/workflows/weekly-summary.yml` |

---

## ❤️ 8️⃣ 커뮤니티 태도 규칙 (Code of Conduct)

> - Respect all contributors.  
> - No personal attacks.  
> - PR discussion = technical, not emotional.  
> - Keep things **simple, reproducible, and readable.**

---

## 🧭 결과

R3C는 이 단계 이후 다음 특징을 갖게 된다:

- **5분 설치, 10분 기여** 가능  
- **자동화된 빌드 / 문서 / CI 환경**  
- **문서 ↔ 코드 1:1 정합성 유지**  
- **누구든지 프로젝트 구조를 쉽게 파악 가능**

---

**문서 버전:** 0.3.0 (LTS 2025-10)  
**작성자:** [@0200134](https://github.com/0200134)  
**위치:** `docs/USER_GUIDE_AND_CONTRIBUTION.md`
