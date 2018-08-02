@echo off
rem Скрипт обновления базы данных
rem update.cmd <объект> <уд.хост> <уд.база данных> <уд.пользователь> <момент обновления> <уд.пароль>

if "%5" equ "" goto NOPARAMS
set pswd=
if not "%6" equ "" set pswd=--password=%6
      
echo.
echo    МКУ Инфоцентр
echo    Объект: %1
echo.
echo    Обновление базы данных
echo.
echo.
echo    ШАГ 1. Получение данных с объекта.
c:\mysql\bin\mysqldump.exe --host=%2 --user=%4 %pswd% --compress --no-create-db --no-create-info "--where=moment>='%5' order by moment" --result-file=..\sql\update_%3.sql %3 points routes vagons accumulators
set exitcode=%errorlevel%
if not %exitcode% equ 0 goto BADEXITCODE
echo.
echo.
echo    ШАГ 2. Подготовка данных
..\cmd\replace.php ..\sql\update_%3.sql INSERT REPLACE
set exitcode=%errorlevel%
if not %exitcode% equ 0 goto BADEXITCODE
echo.
echo.
echo    ШАГ 3. Применение данных на локальном компьютере.
c:\mysql\bin\mysql --host=localhost --user=root --database=%3 --force < ..\sql\update_%3.sql 2>&3
set exitcode=%errorlevel%
if not %exitcode% equ 0 goto BADEXITCODE

..\cmd\apause 5
exit %exitcode%

:NOPARAMS
echo    Ошибка: Недостаточно параметров.
..\cmd\apause 5
exit 1

:BADEXITCODE
echo    Ошибка обновления базы данных.
echo    код = %exitcode%
..\cmd\apause 5
exit %exitcode%
