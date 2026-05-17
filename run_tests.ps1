cmake --build build --target Tests
if ($LASTEXITCODE -ne 0) { exit 1 }

& "build\Tests.exe"