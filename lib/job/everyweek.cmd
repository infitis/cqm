@echo off
rem скрипт, который запускается каждую неделю по расписанию

rem моё имя
call cqmname.cmd

echo. >> ..\..\log\job\everyweek.log
echo. >> ..\..\log\job\everyweek.log
echo. >> ..\..\log\job\everyweek.log
echo =================================== >> ..\..\log\job\everyweek.log
echo   %DATE% %TIME% >> ..\..\log\job\everyweek.log

rem выполняем cmd-срипты
for %%i in ("weekly\cmd\*.cmd" "weekly\cmd\*.bat" ) do (
    echo. >> ..\..\log\job\everyweek.log
    echo ==== %%i  >> ..\..\log\job\everyweek.log
    call %%i >> ..\..\log\job\everyweek.log 2>&1
    echo ==== errorlevel = %errorlevel% ====  >> ..\..\log\job\everyweek.log
    )

rem выполняем sql-срипты
for %%i in ("weekly\sql\*.sql" ) do (
    echo. >> ..\..\log\job\everyweek.log
    echo ==== %%i  >> ..\..\log\job\everyweek.log
    %FBDIR%\bin\isql %cqmname% -u %FB_SCRIPT_USER% -p %FB_SCRIPT_PASS% -i %%i >> ..\..\log\job\everyweek.log 2>&1
    echo ==== errorlevel = %errorlevel% ====  >> ..\..\log\job\everyweek.log
    )
