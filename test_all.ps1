Param(
  [switch]$Debug,
  [switch]$UnitOnly,
  [switch]$PipelineOnly
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

function Invoke-Step($Name, [ScriptBlock]$Action) {
  Write-Host "[STEP] $Name" -ForegroundColor Cyan
  & $Action
}

function Run-Cmd($cmd) {
  Write-Host "[CMD] $cmd" -ForegroundColor DarkGray
  cmd /c $cmd
  if ($LASTEXITCODE -ne 0) { throw "Command failed: $cmd (code=$LASTEXITCODE)" }
}

$repo = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $repo

Invoke-Step 'Configure + Build (CMake/Ninja)' {
  Run-Cmd "cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release"
  Run-Cmd "ninja -C build"
}

if ($Debug) { $env:R3C_DEBUG = '1'; Write-Host "[INFO] Debug enabled (R3C_DEBUG=1)" -ForegroundColor Yellow }

if (-not $PipelineOnly) {
  Invoke-Step 'Unit tests (r3std)' {
    if (-not (Test-Path build)) { New-Item -ItemType Directory -Path build | Out-Null }
    Run-Cmd "rustc +1.65.0 --edition=2021 rustlib\tests.rs --test -o build\tests.exe"
    Run-Cmd "build\tests.exe"
  }
}

if (-not $UnitOnly) {
  Invoke-Step '.r3 fast-path build/run' {
    Run-Cmd "build\r3c.exe examples\main.r3"
    Run-Cmd "build\out_lts.exe"
  }

  Invoke-Step 'C++ transpile build/run' {
    Run-Cmd "build\r3c.exe --transpile-cpp"
    Run-Cmd "build\out_lts.exe"
  }
}

Write-Host "[OK] All tests and runs completed successfully." -ForegroundColor Green
