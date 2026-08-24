@echo off
setlocal

set "SOURCE_DIR=%~dp0"
if "%SOURCE_DIR:~-1%"=="\" set "SOURCE_DIR=%SOURCE_DIR:~0,-1%"
set "MAKEPBO=C:\Program Files (x86)\Mikero\DePboTools\bin\MakePbo.exe"
set "BUILD_DIR=%SOURCE_DIR%\build"

if not exist "%MAKEPBO%" goto tool_missing
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

subst P: /d >nul 2>&1
subst P: "%SOURCE_DIR%"
if errorlevel 1 goto mount_failed

"%MAKEPBO%" -P "-@=KRJ_KeyCardRoomsServer" "P:\KeyCardRoomsServer" "P:\build\KRJ_KeyCardRoomsServer.pbo"
if errorlevel 1 goto build_failed
if not exist "P:\build\KRJ_KeyCardRoomsServer.pbo" goto build_failed

subst P: /d
echo Build complete: %BUILD_DIR%\KRJ_KeyCardRoomsServer.pbo
exit /b 0

:build_failed
subst P: /d >nul 2>&1
echo ERROR: KeyCard Rooms companion build failed.
exit /b 1

:mount_failed
echo ERROR: Could not map P: to %SOURCE_DIR%.
exit /b 1

:tool_missing
echo ERROR: MakePbo.exe not found at %MAKEPBO%.
exit /b 1
