@echo off
setlocal

echo [1/4] C++ 빌드
cmake -B build -S . || goto :fail
cmake --build build || goto :fail

echo [2/4] C++ → Rust 변환 및 Rust 빌드
build\r3c.exe --transpile-all src\main.cpp src\stdlib.cpp || goto :fail

echo [3/4] Rust 실행 파일 실행
if exist build\out_lts.exe (
    build\out_lts.exe
) else (
    echo [ERR] build\out_lts.exe not found!
    goto :fail
)

echo [DONE]
exit /b 0

:fail
echo [FAIL] 빌드/실행 실패
exit /b 1
