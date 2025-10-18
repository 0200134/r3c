# Self-Recompile된 실행 파일 테스트 방법

1. **Rust 변환 및 빌드**
   - `build_and_run.bat` 또는 아래 명령을 실행:
     ```
     cmake -B build -S .
     cmake --build build
     build\r3c.exe --transpile-all src\main.cpp src\stdlib.cpp
     ```
   - 이 과정에서 `build/out_lts_boot.exe`(또는 `build/out_lts.exe`)가 생성됩니다.

2. **self_recompile() 동작 확인**
   - Rust 실행 파일(`build/out_lts.exe`)을 직접 실행:
     ```
     build\out_lts.exe
     ```
   - 실행 로그에 `[r3c-bootstrap] recompiling self via rustc...` 및 `[OK] self-recompile done.` 메시지가 출력되는지 확인합니다.
   - 이때 Rust 코드 내 `self_recompile()` 함수가 실제로 rustc를 호출하여 `build/out_lts_boot.exe`를 새로 빌드합니다.

3. **새로 빌드된 바이너리 실행**
   - self_recompile이 성공하면 `build/out_lts_boot.exe`가 생성됩니다.
   - 이 파일을 직접 실행하여 정상 동작하는지 확인:
     ```
     build\out_lts_boot.exe
     ```
   - `[r3c LTS Rust] running...` 등 기존과 동일한 메시지가 출력되면 self-recompile된 실행 파일도 정상입니다.

4. **요약**
   - `build\out_lts.exe` 실행 → self_recompile()가 `build\out_lts_boot.exe` 생성 → `build\out_lts_boot.exe` 실행 → 정상 동작 확인

**참고:**  
- Windows 환경에서는 실행 중인 바이너리를 덮어쓸 수 없으므로, self_recompile은 항상 다른 이름(`out_lts_boot.exe`)으로 빌드합니다.
- 필요시, `out_lts_boot.exe`를 `out_lts.exe`로 수동 복사하여 교체할 수 있습니다.
