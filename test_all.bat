@echo off
setlocal enabledelayedexpansion

REM Usage: test_all.bat [--debug] [--unit-only] [--pipeline-only] [--rewrite-rs=path\to\file.rs]
set DEBUG=0
set UNITONLY=0
set PIPEONLY=0
set REWRITE_PATH=
for %%A in (%*) do (
  if /I "%%~A"=="--debug" set DEBUG=1
  if /I "%%~A"=="--unit-only" set UNITONLY=1
  if /I "%%~A"=="--pipeline-only" set PIPEONLY=1
  echo %%~A | findstr /I /B /C:"--rewrite-rs=" >nul && (
    set "REWRITE_PATH=%%~A"
  )
)
REM extract path part from --rewrite-rs=...
if defined REWRITE_PATH (
  set "REWRITE_PATH=%REWRITE_PATH:--rewrite-rs=%"
  set "REWRITE_PATH=%REWRITE_PATH:=%"
)

pushd %~dp0

echo [STEP] Configure + Build (CMake/Ninja)
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release || goto :err
ninja -C build || goto :err

if %DEBUG%==1 (
  set R3C_DEBUG=1
  echo [INFO] Debug enabled (R3C_DEBUG=1)
)

if %PIPEONLY%==0 (
  echo [STEP] Unit tests (r3std)
  if not exist build mkdir build
  rustc +1.65.0 --edition=2021 rustlib\tests.rs --test -o build\tests.exe || goto :err
  build\tests.exe || goto :err
)

if %UNITONLY%==0 (
  echo [STEP] .r3 fast-path build/run
  build\r3c.exe examples\main.r3 || goto :err
  build\out_lts.exe || goto :err

  if defined REWRITE_PATH (
    echo [STEP] Rust rewrite build/run -- %REWRITE_PATH%
    build\r3c.exe --rewrite-rs "%REWRITE_PATH%" || goto :err
    build\out_lts.exe || goto :err
  )

  echo [STEP] C++ transpile build/run
  build\r3c.exe --transpile-cpp || goto :err
  build\out_lts.exe || goto :err
)

echo [OK] All tests and runs completed successfully.
popd
exit /b 0

:err
echo [ERR] Failed. Errorlevel=%errorlevel%
popd
exit /b %errorlevel%
