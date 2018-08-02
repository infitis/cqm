@echo off
rem Скрипт восстоновления базы данных (или просто выполнения sql-скрипта)
rem restore.cmd <объект> <dump.sql.gz>

if "%2" equ "" goto NOPARAMS
      
echo.
echo    МКУ Инфоцентр
echo    Объект: %1
echo.
echo    Восстановление базы данных
echo.
echo.
..\magula\mexec.php %2

set exitcode=%errorlevel%
if not %exitcode% equ 0 goto BADEXITCODE

..\cmd\apause 5
exit %exitcode%

:NOPARAMS
echo    Ошибка: Недостаточно параметров.
..\cmd\apause 5
exit 1

:BADEXITCODE
echo    Ошибка восстоновления базы данных.
echo    код = %exitcode%
..\cmd\apause 5
exit %exitcode%
