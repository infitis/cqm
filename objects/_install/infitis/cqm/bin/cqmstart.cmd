@echo off

call cqmname.cmd
cd %CQMDIR%\bin

rem check running apps
..\lib\util\waitsemaphore.exe cqm_server_running_now_semaphore
if errorlevel 1 (
    set RUNNING_SERVER=1
    ) else (
    set RUNNING_SERVER=0
    )

..\lib\util\waitsemaphore.exe cqm_client_running_now_semaphore
if errorlevel 1 (
    set RUNNING_CLIENT=1
    ) else (
    set RUNNING_CLIENT=0
    )

if %RUNNING_SERVER% EQU 1 goto START_APPS
if %RUNNING_CLIENT% EQU 1 goto START_APPS

rem ¯à®¢¥àª  ¡ §ë ¤ ­­ëå
echo.
echo     ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
echo     ³                                                 ³
echo     ³  Ž‚…Š€ €‡› „€›•...                        ³
echo     ³                                                 ³
echo     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
echo.
call ..\lib\dbservice\check.cmd
if %errorlevel% EQU 0 goto DB_TEST_PASSED

echo.
echo     ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
echo     ³                                                 ³
echo     ³  ‚ˆŒ€ˆ…!!!                                    ³
echo     ³                                                 ³
echo     ³  €‡€ „€›• ŒŠ“ Ž‚…†„…€.                    ³
echo     ³                                                 ³
echo     ³  à¨ç¨­®© ¯®¢à¥¦¤¥­¨ï ¬®£«® ¡ëâì                ³
echo     ³  ­¥ª®àà¥ªâ­®¥ § ¢¥àè¥­¨¥ à ¡®âë ª®¬¯ìîâ¥à .     ³
echo     ³                                                 ³
echo     ³  ®¯ëâ âìáï ¢®ááâ ­®¢¨âì ¡ §ã ¤ ­­ëå            ³
echo     ³  ¨§ à¥§¥à¢­®© ª®¯¨¨?                            ³
echo     ³                                                 ³
echo     ³  ˆ ‚Ž‘‘’€Ž‚‹…ˆˆ “„“’ Ž’…Ÿ› „€›…       ³
echo     ³  ‡€ Ž‘‹…„ˆ… 12 —€‘Ž‚ €Ž’›.                  ³
echo     ³                                                 ³
echo     ³  „«ï ¢®ááâ ­®¢«¥­¨ï ­ ¦¬¨â¥ ª« ¢¨èã ENTER       ³
echo     ³  „«ï ®â¬¥­ë ­ ¦¬¨â¥ ª« ¢¨èã ESC                 ³
echo     ³                                                 ³
echo     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
echo.
..\lib\util\getenter.exe
if %errorlevel% EQU 0 (
    rem ¢®ááâ ­ ¢«¨¢ ¥¬
	echo        †„ˆ’…. ˆ„ð’ ‚Ž‘‘’€Ž‚‹…ˆ… €‡› „€›•...
	echo.
    call ..\lib\dbservice\restore.cmd
    if %errorlevel% EQU 0 goto DB_TEST_PASSED else (
echo.
echo     ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
echo     ³                                                 ³
echo     ³  ‚Ž‘‘’€Ž‚ˆ’œ €‡“ „€›• … “„€‹Ž‘œ.           ³
echo     ³                                                 ³
echo     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
echo.

    )
)
echo.
echo     ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
echo     ³                                                 ³
echo     ³  „€‹œ…‰˜€Ÿ €Ž’€ …‚Ž‡ŒŽ†€.                  ³
echo     ³                                                 ³
echo     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
echo.
pause
exit 1	

:DB_TEST_PASSED

rem echo.
rem echo     ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
rem echo     ³                                                 ³
rem echo     ³  Ž’ˆŒˆ‡€–ˆŸ €‡› „€›•...                     ³
rem echo     ³                                                 ³
rem echo     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
rem echo.
rem call ..\lib\dbservice\optimize.cmd
    

:START_APPS
if %RUNNING_SERVER% EQU 0 (
echo.
echo     ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
echo     ³                                                 ³
echo     ³  ‡€“‘Š ŒŠ“ ‘…‚…€...                          ³
echo     ³                                                 ³
echo     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
echo.
start /min cqmsrv.exe
..\lib\util\apause.exe 5
)


if %RUNNING_CLIENT% EQU 0 (
echo.
echo     ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
echo     ³                                                 ³
echo     ³  ‡€“‘Š ŒŠ“ Š‹ˆ…’€...                          ³
echo     ³                                                 ³
echo     ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
echo.
start cqmcli.exe
..\lib\util\apause.exe 5
)

exit 0
