@echo off
cd bin
if "%1"=="debug" (
  :: run debug
  Test-Debug.exe
) else (
  :: run release
  Test.exe
)
pause