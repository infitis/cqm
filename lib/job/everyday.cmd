@echo off
rem �ਯ�, ����� ����᪠���� ����� ���� �� �ᯨᠭ��

rem ��� ���
call cqmname.cmd

echo. >> ..\..\log\job\everyday.log
echo. >> ..\..\log\job\everyday.log
echo. >> ..\..\log\job\everyday.log
echo =================================== >> ..\..\log\job\everyday.log
echo %DATE% %TIME% >> ..\..\log\job\everyday.log

rem �믮��塞 cmd-�ਯ��
for %%i in ("daily\cmd\*.cmd" "daily\cmd\*.bat" ) do (
	echo. >> ..\..\log\job\everyday.log
	echo ====  %%i  >> ..\..\log\job\everyday.log
    call %%i >> ..\..\log\job\everyday.log 2>&1
	echo ==== errorlevel = %errorlevel% ====  >> ..\..\log\job\everyday.log 
	)

rem �믮��塞 sql-�ਯ��
for %%i in ("daily\sql\*.sql" ) do (
	echo. >> ..\..\log\job\everyday.log
	echo ====  %%i  >> ..\..\log\job\everyday.log
    %FBDIR%\bin\isql %cqmname% -u %FB_SCRIPT_USER% -p %FB_SCRIPT_PASS% -i %%i >> ..\..\log\job\everyday.log 2>&1
	echo ==== errorlevel = %errorlevel% ====  >> ..\..\log\job\everyday.log
	)
