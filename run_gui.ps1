cmake --build build --target Lab3QtApp
if ($LASTEXITCODE -ne 0) { exit 1 }

$env:Path = "C:\qt\6.11.0\mingw_64\bin;" + $env:Path
Start-Process -FilePath "build\Lab3QtApp.exe"