## 🧩 PR 요약 (Pull Request Summary)

- **기능명 / 변경 내용**  
  예: `Rust→NASM 변환 로직 개선`, `문서 업데이트`, `테스트 추가`

- **관련 이슈**  
  예: Closes #12, Fixes #8  
  *(없다면 비워도 됩니다)*


---

## 🔍 변경 상세 (Details of Changes)

- 무엇을 수정/추가했는지 구체적으로 설명해주세요.  
  - 예: `if/else` 구문 변환 시 NASM 점프 명령어 최적화  
  - 예: `r3c_spec.md` 문서의 ABI 규칙 6.1 항목 갱신

```diff
- 기존 코드:
  cmp eax, 0
  jne L1
+ 변경 코드:
  test eax, eax
  jnz L1
