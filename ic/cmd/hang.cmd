@echo off
rem Скрипт разрыва соединения
rem hang.cmd <объект> <соединение>

if "%2" equ "" goto NOPARAMS
      
echo.
echo    МКУ Инфоцентр
echo    Объект: %1
echo.
echo    Разрыв соединения
echo.

rasdial %2 /D
set exitcode=%errorlevel%

..\cmd\apause.exe 5
exit %exitcode%

:NOPARAMS
echo    Ошибка: Недостаточно параметров.
exit 1
