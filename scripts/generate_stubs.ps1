# ================================================
# 🧱 R3C Stub Generator (Windows PowerShell Version)
# - UTF-8 safe
# - Removes any .cpp residue in function names
# ================================================

$ErrorActionPreference = "Stop"
$srcDir = "src"

if (-not (Test-Path $srcDir)) {
    New-Item -ItemType Directory -Path $srcDir | Out-Null
}

$files = @(
    "r3c.cpp",
    "r3c_stub.cpp",
    "pkgmgr.cpp",
    "pipeline.cpp",
    "docgen.cpp",
    "formatter.cpp",
    "manifest.cpp",
    "main.cpp",
    "r3cpkg.cpp",
    "stdlib_r3c.cpp",
    "tester.cpp",
    "transpiler.cpp"
)

Write-Host "⚙️ [R3C] Generating stub source files in $srcDir..."

foreach ($f in $files) {
    $path = Join-Path $srcDir $f
    $base = [System.IO.Path]::GetFileNameWithoutExtension($f)
    # ✅ remove any accidental ".cpp" fragments just in case
    $base = $base -replace '\.cpp$', ''
    $func = "r3c_stub_$base"

    Write-Host "🧩 Generating stub: $func() -> $path"
    "void $func() {}" | Out-File -Encoding utf8 $path
}

Write-Host "✅ Stub generation complete. ($($files.Count) files)"
