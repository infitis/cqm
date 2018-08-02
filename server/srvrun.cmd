@echo off
echo.
echo     зддддддддддддддддддддддддддддддддддддддд©
echo     Ё                                       Ё
echo     Ё  ▌├┬└─█┬┘ ┤─▐⌠▒┼─ ▄┼⌠ ▒┘░┌┘░─...      Ё
echo     Ё                                       Ё
echo     юддддддддддддддддддддддддддддддддддддддды
echo.
..\lib\util\waitsemaphore.exe cqm_server_running_now_semaphore 4
if errorlevel 1 goto TIMEOUT
echo                      ok.
start /min cqmsrv.exe
goto BYE

:TIMEOUT
cls
echo.
echo     зддддддддддддддддддддддддддддддддддддддд©
echo     Ё                                       Ё
echo     Ё  ▄┼⌠ ▒┘░┌┘░ ⌠├┘ ░─│▌▓─┘▓ !            Ё
echo     Ё                                       Ё
echo     юддддддддддддддддддддддддддддддддддддддды
echo.
..\lib\util\apause.exe 4
exit

:BYE
echo     ┤─▐⌠≥┘█.
exit