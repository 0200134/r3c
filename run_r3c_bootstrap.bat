@echo off
title r3c Full Bootstrap (C++ → Rust LTS → Self-Rebuild)
chcp 65001 >nul

echo =====================================================
echo [BOOT] r3c full bootstrap pipeline (loop mode)
echo =====================================================

setlocal ENABLEDELAYEDEXPANSION
set "ROOT=C:\rustboot\r3c"
set "BUILD=%ROOT%\build"
set "RUST_VER=1.65.0"

cd /d "%ROOT%"

REM 1️⃣ Rustup 설치/확인
where rustup >nul 2>nul
if %errorlevel% neq 0 (
    echo [SETUP] Rustup not found. Installing...
    powershell -Command "Invoke-WebRequest https://win.rustup.rs/x86_64 -OutFile rustup-init.exe"
    rustup-init.exe -y --default-toolchain stable
    del rustup-init.exe
    echo [PATH] Updating PATH for Rust...
    setx PATH "%USERPROFILE%\.cargo\bin;!PATH!" >nul
)

echo [CHECK] Checking Rust toolchain %RUST_VER%...
rustup toolchain list | find "%RUST_VER%" >nul
if %errorlevel% neq 0 (
    echo [INSTALL] Installing Rust LTS toolchain %RUST_VER%...
    rustup toolchain install %RUST_VER%
) else (
    echo [OK] Rust LTS %RUST_VER% already installed.
)

REM 2️⃣ Clean build folders
if exist "%BUILD%" (
    echo [CLEAN] Removing old build folder...
    rmdir /s /q "%BUILD%"
)
if exist "%ROOT%\out_lts.exe" del /f /q "%ROOT%\out_lts.exe"
if exist "%ROOT%\r3c_lts.exe" del /f /q "%ROOT%\r3c_lts.exe"

REM 3️⃣ C++ → r3c.exe 빌드
echo [CONFIG] Running CMake...
cmake -S . -B build -G "Ninja"
if errorlevel 1 goto :error

echo [BUILD] Compiling r3c.exe...
cmake --build build
if errorlevel 1 goto :error

REM 4️⃣ 트랜스파일 (C++ → Rust)
echo [STEP] Transpiling to Rust LTS...
build\r3c.exe --transpile-all src\main.cpp src\stdlib.cpp
if errorlevel 1 goto :error

REM 5️⃣ Rust LTS 컴파일
if exist "rustlib\r3clib.rs" (
    echo [STEP] Compiling with Rust LTS %RUST_VER%...
    rustup run %RUST_VER% rustc rustlib\r3clib.rs -C opt-level=3 -o r3c_lts.exe
) else (
    echo [ERROR] rustlib\r3clib.rs not found!
    goto :error
)

REM 6️⃣ 자기 자신 실행
if exist "r3c_lts.exe" (
    echo [BOOTSTRAP] Running r3c_lts (self-hosted)...
    r3c_lts.exe --help
) else (
    echo [ERROR] r3c_lts.exe missing!
    goto :error
)

REM 7️⃣ 루프: r3c_lts.exe → 다시 C++ 재생성
echo [LOOP] Initiating self rebuild sequence...
r3c_lts.exe --transpile-all src\main.cpp src\stdlib.cpp
if exist "rustlib\r3clib.rs" (
    echo [REBUILD] Rebuilding self with Rust output...
    rustup run %RUST_VER% rustc rustlib\r3clib.rs -C opt-level=3 -o r3c_lts_rebuild.exe
)

if exist "r3c_lts_rebuild.exe" (
    echo [VERIFY] Running rebuilt self...
    r3c_lts_rebuild.exe --help
    echo [SUCCESS] ✅ Full self-bootstrap loop complete!
) else (
    echo [WARN] ⚠️ Rebuild file not generated.
)

echo =====================================================
echo [DONE] ✅ r3c full bootstrap + self rebuild completed!
echo =====================================================
pause
exit /b 0

:error
echo =====================================================
echo [FAIL] ❌ Bootstrap failed!
echo =====================================================
pause
exit /b 1
