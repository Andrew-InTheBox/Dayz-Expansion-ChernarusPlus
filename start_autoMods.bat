@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
if exist "%SCRIPT_DIR%.env" (
  for /f "usebackq tokens=1,* delims==" %%A in (`findstr /R /C:"^[A-Z_][A-Z0-9_]*=" "%SCRIPT_DIR%.env"`) do (
    set "%%A=%%B"
  )
)

:: ============================================
:: WORKSHOP UPDATES TOGGLE
:: Set to 0 to completely disable all mod/workshop updates
:: ============================================
if not defined ENABLE_WORKSHOP_UPDATES set "ENABLE_WORKSHOP_UPDATES=1"

::Name for the CMD window
set "serverName=KRONJON-Chernarus"
::Server Port
set "serverPort=2302"
::Server config
set "serverConfig=serverDZ.cfg"
::Server profile folder
set "serverProfile=config"
::Logical CPU cores to use (Equal or less than available)
set "serverCPU=4"

:: SteamCMD configuration (required for auto-updating mods)
:: Override any of these in .env for machine-specific config
set "STEAMCMD=C:\steamcmd\steamcmd.exe"
set "STEAM_LOGIN=anonymous"
set "STEAM_PASS="
set "STEAM_GUARD="
set "WORKSHOP_APPID=221100"
if not defined UPDATE_ON_RESTART set "UPDATE_ON_RESTART=1"
if not defined USE_STEAMCMD set "USE_STEAMCMD=0"
if not defined WORKSHOP_PATH set "WORKSHOP_PATH=E:\SteamLibrary\steamapps\workshop\content\221100"
if not defined SKIP_MODS set "SKIP_MODS=_@Heatmap"
if not defined SKIP_MOD_IDS set "SKIP_MOD_IDS=2854246756"
if defined USERNAME set "STEAM_LOGIN=%USERNAME%"
if defined PASSWORD set "STEAM_PASS=%PASSWORD%"

title %serverName% batch

::Build mods list from folders starting with "@"
setlocal enabledelayedexpansion
set "mods="
for /d %%D in (@*) do (
    if not defined mods (
        set "mods=%%~D"
    ) else (
        set "mods=!mods!;%%~D"
    )
)
endlocal & set "mods=%mods%"

echo Server mod list: %mods%

:loop
echo (%time%) Starting %serverName%...

if "%ENABLE_WORKSHOP_UPDATES%"=="1" if "%UPDATE_ON_RESTART%"=="1" call :update_mods

:: /wait = batch pauses until DayZServer_x64.exe exits (graceful shutdown)
start "DayZ Server" /min /wait DayZServer_x64.exe ^
  -config=%serverConfig% ^
  "-mod=%mods%" ^
  "-serverMod=_@Heatmap;_@DayZ-Dynamic-AI-Addon" ^
  -port=%serverPort% ^
  -profiles=%serverProfile% ^
  -cpuCount=%serverCPU% ^
  -adminlog -netlog -freezecheck

echo (%time%) Server process exited. Restarting in 3 seconds...
timeout /t 3 /nobreak >nul
goto loop

:update_mods
if /i "%USE_STEAMCMD%"=="1" call :update_with_steamcmd
if /i not "%USE_STEAMCMD%"=="1" call :update_from_workshop
goto :eof

:update_with_steamcmd
if not exist "%STEAMCMD%" goto :steamcmd_missing

for %%I in ("%STEAMCMD%") do set "STEAMCMD_DIR=%%~dpI"
set "WORKSHOP_DIR=%STEAMCMD_DIR%steamapps\workshop\content\%WORKSHOP_APPID%"

set "LOGIN_ARGS=+login %STEAM_LOGIN%"
if /i "%STEAM_LOGIN%"=="anonymous" set "LOGIN_ARGS=+login anonymous"
if /i not "%STEAM_LOGIN%"=="anonymous" (
  if exist "%STEAMCMD_DIR%config\config.vdf" (
    set "LOGIN_ARGS=+login %STEAM_LOGIN%"
  ) else (
    if not "%STEAM_PASS%"=="" set "LOGIN_ARGS=+login %STEAM_LOGIN% %STEAM_PASS% %STEAM_GUARD%"
  )
)

set "STEAMCMD_SCRIPT=%STEAMCMD_DIR%steamcmd_workshop.txt"
set "QUEUED=0"
> "%STEAMCMD_SCRIPT%" echo %LOGIN_ARGS:+=%
for /d %%D in (@* _@*) do call :maybe_queue_update "%%D"
if "%QUEUED%"=="0" (
  del "%STEAMCMD_SCRIPT%" >nul 2>&1
  goto :eof
)
>> "%STEAMCMD_SCRIPT%" echo quit
echo (%time%) Updating mods in one SteamCMD session...
"%STEAMCMD%" +runscript "%STEAMCMD_SCRIPT%"
del "%STEAMCMD_SCRIPT%" >nul 2>&1
call :check_sentry
for /d %%D in (@* _@*) do call :maybe_copy_from_workshop "%%D"
goto :eof

:maybe_queue_update
call :is_skipped "%~1"
if "%SKIP%"=="1" goto :skip_mod_update
call :queue_update "%~1"
goto :eof

:queue_update
setlocal EnableDelayedExpansion
set "MOD_DIR=%~1"
if not exist "!MOD_DIR!\meta.cpp" goto :skip_nometa
set "MOD_ID="
for /f "tokens=2 delims==;" %%I in ('findstr /i "publishedid" "!MOD_DIR!\meta.cpp"') do set "MOD_ID=%%I"
set "MOD_ID=!MOD_ID: =!"
if "!MOD_ID!"=="" goto :skip_noid
echo (%time%) Queued !MOD_DIR! (workshop !MOD_ID!)
>> "%STEAMCMD_SCRIPT%" echo workshop_download_item %WORKSHOP_APPID% !MOD_ID! validate
endlocal & set "QUEUED=1"
goto :eof

:update_from_workshop
if not exist "%WORKSHOP_PATH%" goto :workshop_path_missing
set "WORKSHOP_DIR=%WORKSHOP_PATH%"
if exist "%WORKSHOP_DIR%\%WORKSHOP_APPID%" set "WORKSHOP_DIR=%WORKSHOP_DIR%\%WORKSHOP_APPID%"
if exist "%WORKSHOP_DIR%\content\%WORKSHOP_APPID%" set "WORKSHOP_DIR=%WORKSHOP_DIR%\content\%WORKSHOP_APPID%"
echo (%time%) Using workshop cache: %WORKSHOP_DIR%
for /d %%D in (@* _@*) do call :maybe_copy_from_workshop "%%D"
goto :eof

:maybe_update_one
call :is_skipped "%~1"
if "%SKIP%"=="1" goto :skip_mod_update
call :update_one "%~1"
goto :eof

:maybe_copy_from_workshop
call :is_skipped "%~1"
if "%SKIP%"=="1" goto :skip_mod_copy
call :copy_from_workshop "%~1"
goto :eof

:skip_mod_update
echo (%time%) Skipping %~1 (in SKIP_MODS)
goto :eof

:skip_mod_copy
echo (%time%) Skipping %~1 (in SKIP_MODS)
goto :eof

:update_one
call :is_skipped "%~1"
if "%SKIP%"=="1" goto :skip_mod_update
setlocal EnableDelayedExpansion
set "MOD_DIR=%~1"
if not exist "!MOD_DIR!\meta.cpp" goto :skip_nometa

set "MOD_ID="
for /f "tokens=2 delims==;" %%I in ('findstr /i "publishedid" "!MOD_DIR!\meta.cpp"') do set "MOD_ID=%%I"
set "MOD_ID=!MOD_ID: =!"
if "!MOD_ID!"=="" goto :skip_noid

echo (%time%) Updating !MOD_DIR! (workshop !MOD_ID!)
"%STEAMCMD%" !LOGIN_ARGS! +workshop_download_item %WORKSHOP_APPID% !MOD_ID! validate +quit
if exist "%WORKSHOP_DIR%\!MOD_ID!" goto :copy_mod
goto :missing_mod

:copy_mod
if not exist "!MOD_DIR!" mkdir "!MOD_DIR!"
robocopy "%WORKSHOP_DIR%\!MOD_ID!" "!MOD_DIR!" /MIR /FFT /Z /XA:H /W:2 /R:2 >nul
endlocal & goto :eof

:missing_mod
echo (%time%) WARNING: Workshop content not found for !MOD_ID!
endlocal & goto :eof

:copy_from_workshop
set "MOD_DIR=%~1"
setlocal EnableDelayedExpansion
if not exist "!MOD_DIR!\meta.cpp" goto :skip_nometa_ws
set "MOD_ID="
for /f "tokens=2 delims==;" %%I in ('findstr /i "publishedid" "!MOD_DIR!\meta.cpp"') do set "MOD_ID=%%I"
set "MOD_ID=!MOD_ID: =!"
endlocal & set "MOD_ID=%MOD_ID%"
if "%MOD_ID%"=="" goto :skip_noid_ws
if exist "%WORKSHOP_DIR%\%MOD_ID%" goto :copy_mod_ws
goto :missing_mod_ws

:copy_mod_ws
echo (%time%) Syncing %MOD_DIR% from workshop cache %MOD_ID%
if not exist "%MOD_DIR%" mkdir "%MOD_DIR%"
robocopy "%WORKSHOP_DIR%\%MOD_ID%" "%MOD_DIR%" /MIR /FFT /Z /XA:H /W:2 /R:2 >nul
goto :eof

:missing_mod_ws
echo (%time%) WARNING: Workshop cache missing for %MOD_ID%
goto :eof

:skip_nometa_ws
echo (%time%) Skipping %MOD_DIR% (no meta.cpp)
endlocal & goto :eof

:skip_noid_ws
echo (%time%) Skipping %MOD_DIR% (no publishedid)
goto :eof

:skip_nometa
echo (%time%) Skipping !MOD_DIR! (no meta.cpp)
endlocal & goto :eof

:skip_noid
echo (%time%) Skipping !MOD_DIR! (no publishedid)
endlocal & goto :eof

:is_skipped
setlocal EnableDelayedExpansion
set "SKIP=0"
set "MOD_DIR=%~1"
for %%S in (%SKIP_MODS%) do (
    if /i "%%S"=="%MOD_DIR%" set "SKIP=1"
)
if "!SKIP!"=="0" if exist "%MOD_DIR%\meta.cpp" (
  set "MOD_ID="
  for /f "tokens=2 delims==;" %%I in ('findstr /i "publishedid" "%MOD_DIR%\meta.cpp"') do set "MOD_ID=%%I"
  set "MOD_ID=!MOD_ID: =!"
  if not "!MOD_ID!"=="" (
    for %%S in (%SKIP_MOD_IDS%) do (
      if "%%S"=="!MOD_ID!" set "SKIP=1"
    )
  )
)
endlocal & set "SKIP=%SKIP%"
goto :eof

:check_sentry
setlocal
set "SENTRY_FOUND=0"
for %%F in ("%STEAMCMD_DIR%ssfn*") do set "SENTRY_FOUND=1"
if "%SENTRY_FOUND%"=="0" (
  echo ^(%time%^) WARNING: Steam Guard sentry file not found in "%STEAMCMD_DIR%". You may be prompted again.
) else (
  echo ^(%time%^) Steam Guard sentry file detected.
)
if exist "%STEAMCMD_DIR%config\config.vdf" (
  echo ^(%time%^) SteamCMD config token found: "%STEAMCMD_DIR%config\config.vdf"
) else (
  echo ^(%time%^) WARNING: SteamCMD config token missing: "%STEAMCMD_DIR%config\config.vdf"
)
endlocal & goto :eof

:steamcmd_missing
echo (%time%) SteamCMD not found at "%STEAMCMD%". Skipping mod updates.
goto :eof

:workshop_path_missing
echo (%time%) Workshop path not found at "%WORKSHOP_PATH%". Skipping mod updates.
goto :eof
