# 🚀 R3C 개선 및 자동화 실행계획  
> “No C. No LLVM. Only Rust and Assembly.”  
> _Self-hosted Rust compiler bootstrap project._

---

## ✅ 1️⃣ 워크플로우 자동화 전체 점검 (CI / CD / Actions)

### 🎯 목표
모든 빌드, 테스트, 문서 갱신이 **자동으로 동작**하고  
에러 발생 시 **즉시 GitHub Actions 알림으로 확인 가능**하게 만든다.

### 🔧 해야 할 일
- `.github/workflows/` 아래 다음 3개 파일 생성 또는 수정:
  1. **`project-auto.yml`** — 이슈/PR 자동 보드 이동  
  2. **`test-build.yml`** — PR 및 main push 시 자동 빌드  
  3. **`weekly-summary.yml`** — 주간 활동 요약 자동 업데이트  

### 💡 구현 예시
```yaml
# .github/workflows/test-build.yml
name: R3C Build Test
on:
  push:
    branches: [main]
  pull_request:
    branches: [main]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Install dependencies
        run: sudo apt-get update && sudo apt-get install -y cmake nasm
      - name: Configure
        run: cmake -B build -S .
      - name: Build
        run: cmake --build build --config Release -j4
      - name: Verify
        run: test -f build/r3c && echo "✅ Build OK" || (echo "❌ Build failed" && exit 1)
```

---

## ✅ 2️⃣ 코드 ↔ 문서 완전 동기화

### 🎯 목표
모든 함수, 구조체, 모듈이 **문서화와 실제 코드가 일치하도록 관리**된다.

### 📚 해야 할 일
- `docs/R3C_Source_Map.md` 유지: 실제 코드 변경 시 수동 업데이트.  
- `scripts/auto_docgen.py` 작성: C++ 소스에서 함수 시그니처 추출 → `.md` 자동 업데이트.  
- `README.md`의 명령어 예시가 실행 가능한지 주기적 검증.

### 🧰 예시 스크립트
```python
# scripts/auto_docgen.py
import re, glob
with open("docs/R3C_Source_Map.md", "w", encoding="utf-8") as out:
    out.write("# Auto-generated Source Map\n\n")
    for file in glob.glob("src/**/*.cpp", recursive=True):
        out.write(f"## {file}\n")
        for line in open(file, encoding="utf-8"):
            if re.match(r"^\w.*\(", line.strip()) and "{" in line:
                out.write(f"- `{line.strip()}`\n")
```

---

## ✅ 3️⃣ 기여 및 사용 문서 강화 (Community & Onboarding)

### 🎯 목표
외부 기여자들이 **“바로 참여할 수 있게”** 만든다.  
지침은 명확하고, PR 프로세스는 직관적이어야 한다.

### 📋 해야 할 일
- `CONTRIBUTING.md` 추가:
  ```md
  ## Contributing Guide
  - 브랜치 이름 규칙: `feature/*`, `fix/*`
  - 커밋 메시지: `[scope]: message` 형식 (예: `[transpiler]: add lexer support`)
  - `.c` 확장자는 허용되지 않음.
  - `cmake -B build -S . && cmake --build build` 로 테스트 후 PR 생성.
  ```
- `.github/ISSUE_TEMPLATE/bug_report.yml`
- `.github/PULL_REQUEST_TEMPLATE.md`
- “첫 PR”용 `good first issue` 라벨 지정  

### 💡 효과
- 외부 개발자 참여 유도  
- 문서와 코드 일관성 유지  
- 커뮤니티 활성화 기반 구축  

---

## ✅ 4️⃣ 프로젝트 상태 시각화 (Roadmap & Milestone)

### 🎯 목표
현재 진행 상황을 누구나 한눈에 볼 수 있게 함.  
(진행률, 완료 항목, 예정 기능)

### 🔧 해야 할 일
- `docs/ROADMAP.md` 작성:
  ```md
  ## Phase 1 — Rust → NASM 변환기 ✅ 완료
  ## Phase 2 — NASM → EXE 링크 체인 🔄 진행 중
  ## Phase 3 — Bootstrap (R3C로 R3C 빌드) ⏳ 계획
  ## Phase 4 — R3C-LTS 배포 및 독립 Rust 환경 구축 🚀 예정
  ```
- GitHub Projects 보드 → 칸 이름:
  ```
  🧩 Todo | 🛠 In Progress | ✅ Done
  ```
- 이슈 자동 분류 (`project-auto.yml` 사용)

---

## 🏁 요약 (실행 순서)
1. **워크플로 자동화** → Actions 3종 정비  
2. **문서 동기화** → 코드와 문서 구조 통합  
3. **기여 시스템** → CONTRIBUTING, ISSUE 템플릿 도입  
4. **진행 시각화** → Project 보드 및 Roadmap.md 정리  

---

## 🧠 최종 결과
R3C는 이후 다음 상태에 도달하게 된다:

- ✅ 완전 자동화된 빌드 & CI 체인  
- ✅ 최신 코드와 일치하는 문서  
- ✅ 외부 기여자 onboarding 구조 완비  
- ✅ 진행 상황이 명확히 공개된 투명한 프로젝트  

---
