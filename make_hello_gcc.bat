@echo off
setlocal
cd /d %~dp0

rem 1) out.asm 생성
if not exist build\r3c.exe (
  echo [ERR] build\r3c.exe not found. Run CMake build first.
  exit /b 1
)
.\build\r3c.exe examples\main.r3 || exit /b 1

rem 2) nasm
if not exist "C:\Program Files\NASM\nasm.exe" (
  where nasm >nul 2>nul || (echo [ERR] nasm not found in PATH & exit /b 1)
  set NASM=nasm
) else (
  set NASM="C:\Program Files\NASM\nasm.exe"
)
%NASM% -f win64 out.asm -o out.obj || exit /b 1

rem 3) gcc 링크 (MinGW)
where gcc >nul 2>nul || (echo [ERR] gcc not found in PATH & exit /b 1)
gcc -o hello.exe out.obj -Wl,-e,main -Wl,--subsystem,console -lmsvcrt -lkernel32 || (
  echo [WARN] retry with group order...
  gcc -o hello.exe out.obj -Wl,-e,main -Wl,--subsystem,console -Wl,--start-group -lmsvcrt -lkernel32 -Wl,--end-group || exit /b 1
)

echo.
echo ✅ Build complete. Running...
.\hello.exe
echo ExitCode=%ERRORLEVEL%
endlocal
