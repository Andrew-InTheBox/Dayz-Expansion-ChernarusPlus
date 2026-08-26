@echo off
setlocal

set "SOURCE_ROOT=%~dp0"
if "%SOURCE_ROOT:~-1%"=="\" set "SOURCE_ROOT=%SOURCE_ROOT:~0,-1%"
set "COMPANION_ROOT=%SOURCE_ROOT%\..\KeyCard-Rooms-Server"
set "MAKEPBO=C:\Program Files (x86)\Mikero\DePboTools\bin\MakePbo.exe"
set "KEYTOOLS=D:\SteamLibrary\steamapps\common\DayZ Tools\Bin\DsUtils"
set "KEY_NAME=ChernaTraderSecureRooms_v1"
set "OUTPUT_ROOT=%SOURCE_ROOT%\build\ChernaTraderSecureRooms"
set "MOD_ROOT=%OUTPUT_ROOT%\@ChernaTrader-SecureRooms"
set "ADDONS_DIR=%MOD_ROOT%\Addons"
set "KEYS_DIR=%MOD_ROOT%\Keys"
set "PRIVATE_KEY_DIR=%SOURCE_ROOT%\private_keys"
set "VENDOR_MOD=%SOURCE_ROOT%\..\..\@KeyCard-Rooms"
if exist "%SOURCE_ROOT%\..\..\_@KeyCard-Rooms-VendorBackup\Addons" set "VENDOR_MOD=%SOURCE_ROOT%\..\..\_@KeyCard-Rooms-VendorBackup"

if not exist "%MAKEPBO%" goto tool_missing
if not exist "%KEYTOOLS%\DSCreateKey.exe" goto tool_missing
if not exist "%KEYTOOLS%\DSSignFile.exe" goto tool_missing

if not exist "%ADDONS_DIR%" mkdir "%ADDONS_DIR%"
if not exist "%KEYS_DIR%" mkdir "%KEYS_DIR%"
if not exist "%PRIVATE_KEY_DIR%" mkdir "%PRIVATE_KEY_DIR%"

if not exist "%PRIVATE_KEY_DIR%\%KEY_NAME%.biprivatekey" (
    pushd "%PRIVATE_KEY_DIR%"
    "%KEYTOOLS%\DSCreateKey.exe" "%KEY_NAME%"
    if errorlevel 1 goto key_failed
    popd
)

copy /y "%PRIVATE_KEY_DIR%\%KEY_NAME%.bikey" "%KEYS_DIR%\%KEY_NAME%.bikey" >nul

subst P: /d >nul 2>&1
subst P: "%SOURCE_ROOT%"
if errorlevel 1 goto mount_failed

call :pack "KeyCardSystem" "KeyCardSystem.pbo"
if errorlevel 1 goto build_failed
call :pack "KeyCardSystemServer" "KeyCardSystemServer.pbo"
if errorlevel 1 goto build_failed
call :pack "KeyCardSystemServerConfig" "KeyCardSystemServerConfig.pbo"
if errorlevel 1 goto build_failed
rem The client asset PBOs are unchanged. Reuse their proven binaries rather
rem than reprocessing ODOL models through a partially mounted P: drive.
copy /y "%VENDOR_MOD%\Addons\KlimaX_Doors.pbo" "%ADDONS_DIR%\KlimaX_Doors.pbo" >nul
if errorlevel 1 goto build_failed
copy /y "%VENDOR_MOD%\Addons\RedemptionKeyCards.pbo" "%ADDONS_DIR%\RedemptionKeyCards.pbo" >nul
if errorlevel 1 goto build_failed

subst P: /d
subst P: "%COMPANION_ROOT%"
if errorlevel 1 goto mount_failed
"%MAKEPBO%" -P "-@=KRJ_KeyCardRoomsServer" "P:\KeyCardRoomsServer" "%ADDONS_DIR%\KRJ_KeyCardRoomsServer.pbo"
if errorlevel 1 goto build_failed

for %%F in ("%ADDONS_DIR%\*.pbo") do (
    "%KEYTOOLS%\DSSignFile.exe" "%PRIVATE_KEY_DIR%\%KEY_NAME%.biprivatekey" "%%~fF"
    if errorlevel 1 goto sign_failed
)

copy /y "%SOURCE_ROOT%\workshop\mod.cpp" "%MOD_ROOT%\mod.cpp" >nul
copy /y "%SOURCE_ROOT%\workshop\meta.cpp" "%MOD_ROOT%\meta.cpp" >nul
subst P: /d >nul 2>&1
echo Build and signing complete: %MOD_ROOT%
exit /b 0

:pack
"%MAKEPBO%" -P "-@=%~1" "P:\%~1" "%ADDONS_DIR%\%~2"
exit /b %errorlevel%

:build_failed
subst P: /d >nul 2>&1
echo ERROR: PBO build failed.
exit /b 1

:sign_failed
subst P: /d >nul 2>&1
echo ERROR: PBO signing failed.
exit /b 1

:mount_failed
subst P: /d >nul 2>&1
echo ERROR: Could not map source directory to P:.
exit /b 1

:key_failed
popd
echo ERROR: Signing key generation failed.
exit /b 1

:tool_missing
echo ERROR: Required PBO or signing tools were not found.
exit /b 1
