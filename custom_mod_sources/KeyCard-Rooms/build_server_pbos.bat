@echo off
setlocal

set "SOURCE_ROOT=%~dp0"
if "%SOURCE_ROOT:~-1%"=="\" set "SOURCE_ROOT=%SOURCE_ROOT:~0,-1%"
set "MAKEPBO=C:\Program Files (x86)\Mikero\DePboTools\bin\MakePbo.exe"
set "BUILD_DIR=%SOURCE_ROOT%\build"

if not exist "%MAKEPBO%" (
    echo ERROR: MakePbo was not found at "%MAKEPBO%".
    exit /b 1
)

if exist P:\NUL (
    echo ERROR: P: is already in use. Unmount it or adjust this build script.
    exit /b 1
)

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

subst P: "%SOURCE_ROOT%"
if errorlevel 1 (
    echo ERROR: Could not map the source directory to P:.
    exit /b 1
)

"%MAKEPBO%" -P "-@=KeyCardSystemServer" "P:\KeyCardSystemServer" "P:\build\KeyCardSystemServer.pbo"
if errorlevel 1 goto build_failed
if not exist "P:\build\KeyCardSystemServer.pbo" goto build_failed

"%MAKEPBO%" -P "-@=KeyCardSystemServerConfig" "P:\KeyCardSystemServerConfig" "P:\build\KeyCardSystemServerConfig.pbo"
if errorlevel 1 goto build_failed
if not exist "P:\build\KeyCardSystemServerConfig.pbo" goto build_failed

subst P: /D
echo.
echo Build complete:
echo   %BUILD_DIR%\KeyCardSystemServer.pbo
echo   %BUILD_DIR%\KeyCardSystemServerConfig.pbo
exit /b 0

:build_failed
subst P: /D
echo ERROR: KeyCard Rooms PBO build failed.
exit /b 1
