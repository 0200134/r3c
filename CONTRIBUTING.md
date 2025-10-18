# 🤝 Contributing to R3C

> “No C. No LLVM. Only Rust and Assembly.”  
> R3C is an experimental Rust compiler bootstrap — aiming for a self-hosted ecosystem.

---

## 🧠 Philosophy

R3C는 단순히 코드를 짜는 프로젝트가 아니다.  
Rust가 **C나 LLVM 없이 독립적으로 살아남을 수 있는지 실험하는 엔진**이다.  
기여자는 “Rust 독립성 실현”이라는 큰 목표를 공유해야 한다.

---

## ⚙️ 환경 세팅

### 🪟 Windows
```bash
git clone https://github.com/0200134/r3c.git
cd r3c
cmake -B build -S .
cmake --build build --config Release
```

### 🐧 Linux
```bash
sudo apt install cmake nasm -y
git clone https://github.com/0200134/r3c.git
cd r3c
cmake -B build -S .
cmake --build build -j4
```

---

## 🧩 브랜치 규칙

| 목적 | 브랜치 접두사 | 예시 |
|------|---------------|------|
| 새 기능 | `feature/` | `feature/linker-pipeline` |
| 버그 수정 | `fix/` | `fix/tokenizer-bug` |
| 문서 보강 | `docs/` | `docs/update-readme` |
| 리팩터링 | `refactor/` | `refactor/ast-cleanup` |

```bash
git checkout -b feature/my-feature
```

---

## 🧱 커밋 규칙

커밋 메시지는 반드시 `[scope]: action` 형태로 작성한다.

| 예시 | 설명 |
|------|------|
| `[transpiler]: add match expression` | 트랜스파일러 기능 추가 |
| `[linker]: fix ELF output bug` | 링커 오류 수정 |
| `[docs]: update linking pipeline spec` | 문서 보강 |
| `[ci]: add build workflow` | 자동화 수정 |

---

## 🔍 코드 스타일

- **C++17 이상** 사용  
- **탭 대신 4칸 스페이스**  
- **함수명:** `camelCase()`  
- **클래스명:** `PascalCase`  
- **전역 변수 금지** (모두 구조체/클래스 스코프로 한정)  
- 모든 파일 끝에는 개행 필수  

---

## 🧪 테스트 및 빌드 검증

PR 제출 전에 반드시 실행:

```bash
cmake -B build -S .
cmake --build build
```

빌드 후:
- `build/r3c` 또는 `build/r3c.exe` 생성 확인  
- `r3c --emit-asm --asm-out build/out.asm` 동작 확인  

---

## 🧰 PR 생성 절차

1. Fork → Clone → 새 브랜치 생성  
2. 코드 수정 및 빌드 확인  
3. 커밋 & 푸시:
   ```bash
   git add .
   git commit -m "[scope]: message"
   git push origin feature/my-feature
   ```
4. GitHub에서 Pull Request 생성  
5. CI (GitHub Actions) 빌드 통과 시 자동 리뷰 요청됨  
6. 승인되면 merge 처리  

---

## 🧾 Issue 작성 규칙

이슈는 명확한 “문제 → 기대 동작” 구조로 작성.

**예시:**
```text
### 문제
`r3c --link` 실행 시 out.elf가 생성되지 않음

### 기대 동작
정상 링크 후 실행 가능한 out.elf 생성

### 환경
OS: Ubuntu 24.04
CMake: 3.28
NASM: 2.16
```

---

## 🧠 리뷰 원칙

- 기술적 논의만 허용 (인신공격, 감정표현 금지)  
- PR은 최소 1명의 리뷰 승인 후 머지  
- 코드 스타일 및 빌드 테스트 불통 시 반려  

---

## ❤️ 코드 기여 외 방법

- 문서 보강 (`docs/*.md`)  
- 버그 리포트 및 아이디어 제안  
- 번역, UI, 자동화 지원  
- Rust 파트(`rustlib/`) 개선  

---

## 📜 License

모든 기여물은 MIT License로 통합된다.  
PR 제출 시 해당 조건에 자동 동의한 것으로 간주된다.

---

**작성자:** [@0200134](https://github.com/0200134)  
**문서 버전:** 1.0.0 (2025-10)  
**위치:** `CONTRIBUTING.md`
