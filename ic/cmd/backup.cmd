@echo off
rem Скрипт резервирования базы данных
rem backup.cmd <объект> <база данных> <директория для дампа>

if "%3" equ "" goto NOPARAMS
      
echo.
echo    МКУ Инфоцентр
echo    Объект: %1
echo.
echo    Резервирование базы данных
echo    Директория для резерва: %3
echo.
echo.
..\magula\mbu.php %2 -b%3

set exitcode=%errorlevel%
if not %exitcode% equ 0 goto BADEXITCODE

..\cmd\apause 5
exit %exitcode%

:NOPARAMS
echo    Ошибка: Недостаточно параметров.
..\cmd\apause 5
exit 1

:BADEXITCODE
echo    Ошибка резервирования базы данных.
echo    код = %exitcode%
..\cmd\apause 5
exit %exitcode%
