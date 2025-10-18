# r3c 자동 실행 스크립트
# 파일 이름: run_r3c.ps1
# 위치: C:\rustboot\r3c\run_r3c.ps1

Write-Host "[BOOT] r3c full pipeline starting..." -ForegroundColor Cyan

# 1️⃣ 프로젝트 폴더 이동
Set-Location "C:\rustboot\r3c"

# 2️⃣ 기존 build 폴더 제거
if (Test-Path "build") {
    Write-Host "[CLEAN] Removing previous build folder..."
    Remove-Item -Recurse -Force build
}

# 3️⃣ CMake 설정
Write-Host "[CONFIG] Running cmake..."
cmake -S . -B build -G "Ninja"

# 4️⃣ 빌드
Write-Host "[BUILD] Compiling with Ninja..."
cmake --build build

# 5️⃣ r3c.exe 실행
Write-Host "[RUN] Running transpiler..."
.\build\r3c.exe --transpile-all src\main.cpp src\stdlib.cpp

# 6️⃣ Rust 빌드 결과 실행 파일 존재 시 실행
if (Test-Path "out_lts.exe") {
    Write-Host "[RUN] Executing transpiled Rust binary..."
    .\out_lts.exe
} else {
    Write-Host "[WARN] No Rust output found (out_lts.exe missing)."
}

Write-Host "[DONE] All steps completed." -ForegroundColor Green
