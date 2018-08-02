@echo off
rem скрипт, который запускается каждый день по расписанию

rem моё имя
call cqmname.cmd

echo. >> ..\..\log\job\everyday.log
echo. >> ..\..\log\job\everyday.log
echo. >> ..\..\log\job\everyday.log
echo =================================== >> ..\..\log\job\everyday.log
echo %DATE% %TIME% >> ..\..\log\job\everyday.log

rem выполняем cmd-срипты
for %%i in ("daily\cmd\*.cmd" "daily\cmd\*.bat" ) do (
	echo. >> ..\..\log\job\everyday.log
	echo ====  %%i  >> ..\..\log\job\everyday.log
    call %%i >> ..\..\log\job\everyday.log 2>&1
	echo ==== errorlevel = %errorlevel% ====  >> ..\..\log\job\everyday.log 
	)

rem выполняем sql-срипты
for %%i in ("daily\sql\*.sql" ) do (
	echo. >> ..\..\log\job\everyday.log
	echo ====  %%i  >> ..\..\log\job\everyday.log
    %FBDIR%\bin\isql %cqmname% -u %FB_SCRIPT_USER% -p %FB_SCRIPT_PASS% -i %%i >> ..\..\log\job\everyday.log 2>&1
	echo ==== errorlevel = %errorlevel% ====  >> ..\..\log\job\everyday.log
	)
