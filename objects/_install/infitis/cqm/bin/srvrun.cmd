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

:BYE
..\lib\util\apause.exe 5
echo     ┤─▐⌠≥┘█.
