@echo off
rem �ਯ�, ����� ����᪠���� ������ ������ �� �ᯨᠭ��

rem ��� ���
call cqmname.cmd

echo. >> ..\..\log\job\everyweek.log
echo. >> ..\..\log\job\everyweek.log
echo. >> ..\..\log\job\everyweek.log
echo =================================== >> ..\..\log\job\everyweek.log
echo   %DATE% %TIME% >> ..\..\log\job\everyweek.log

rem �믮��塞 cmd-�ਯ��
for %%i in ("weekly\cmd\*.cmd" "weekly\cmd\*.bat" ) do (
    echo. >> ..\..\log\job\everyweek.log
    echo ==== %%i  >> ..\..\log\job\everyweek.log
    call %%i >> ..\..\log\job\everyweek.log 2>&1
    echo ==== errorlevel = %errorlevel% ====  >> ..\..\log\job\everyweek.log
    )

rem �믮��塞 sql-�ਯ��
for %%i in ("weekly\sql\*.sql" ) do (
    echo. >> ..\..\log\job\everyweek.log
    echo ==== %%i  >> ..\..\log\job\everyweek.log
    %FBDIR%\bin\isql %cqmname% -u %FB_SCRIPT_USER% -p %FB_SCRIPT_PASS% -i %%i >> ..\..\log\job\everyweek.log 2>&1
    echo ==== errorlevel = %errorlevel% ====  >> ..\..\log\job\everyweek.log
    )
