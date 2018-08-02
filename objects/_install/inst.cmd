@echo off
rem -----------------------------------------------------------------
rem ��ਯ� ���⠫��樨 �ணࠬ����� ���ᯥ祭�� �������� ���
rem ����� 3.0 ��� Windows 2000/XP
rem Copyright (C) 2004 ��᫠� ����, 2006 �����
rem -----------------------------------------------------------------

echo.
echo.
echo ----------------------------------------
echo     ���⠫���� �� �������� ���
echo ----------------------------------------
echo.
echo.
echo ��������!
echo ��� ࠡ��� �� ��� ����室���, �� �� �뫨 ��⠭������:
echo * ��ࢥ� Firebird (����� 1.5.2 � ���), ����饭 ��� �㦡�
echo * �������� PHP (cli) (����� 5.1.1 � ���)
echo.
pause

rem project name
echo.
echo ��� 0. ��� �஥�� (cqmname).
echo ----------------------------------------
echo ����஢���� 䠩��...
xcopy .\infitis\cqm\bin\cqmname.cmd %windir%\system32 /f /y /q
echo     ok.
echo �����...
call cqmname.cmd
echo     ok.

rem firebird instalation
echo.
echo ��� 1. �஢�ઠ �ࢥ� Firebird
echo ----------------------------------------
echo �஢�ઠ fbserver.exe...
if not exist %FBDIR%\bin\fbserver.exe (
	echo     �� ������.
	goto NO_FB
	)
echo     ok.
echo �஢�ઠ ������᪮� ������⥪�...
if not exist %FBDIR%\bin\instclient.exe (
	echo     �� ������ instclient.exe
	goto NO_FB
	)
%FBDIR%\bin\instclient query fbclient
if %errorlevel% NEQ 0 (
	echo 	�� �������.
	goto NO_FB
	)
echo     ok.
echo �஢�ઠ �㦡�...
for /f %%i in ('net start') do if "%%i" EQU "Firebird" (
	echo     ok.
	goto INSTALLED_FB
	)
echo     �� ����饭�.

:NO_FB
echo.
echo.
echo         ���������� ���������� ����������.
echo         �஢�ઠ Firebird �� �ன����.
echo.
echo         ���⠫��� ��ࢠ��!
echo.
pause
goto THE_END

:INSTALLED_FB

rem php instalation
echo.
echo ��� 2. �஢�ઠ �������� php
echo ----------------------------------------
echo �஢�ઠ ���樠権 .cphp � .php...
assoc .cphp
if %errorlevel% NEQ 0 goto NO_PHP
ftype php.cqm.script
if %errorlevel% NEQ 0 goto NO_PHP
echo     ok.

goto STEP_3

:NO_PHP
echo.
echo.
echo         ���������� ���������� ����������.
echo         �஢�ઠ php �� �ன����.
echo.
echo         ���⠫��� ��ࢠ��!
echo.
pause
goto THE_END


:STEP_3
echo.
echo.
echo ��� 3. ����஢���� 䠩��� �� ����.
echo ----------------------------------------
xcopy .\infitis c:\infitis\ /f /y /s /e /q
echo     ok.


echo.
echo ��� 4. ���� ������
echo ----------------------------------------
echo ������ � aliases.conf...
for /F "eol=# delims== " %%i in (%FBDIR%\aliases.conf) do (
	if /i %%i EQU %cqmname% goto EXIST_ALIAS
	)	
echo     �� �������, ����������...
echo %cqmname%=%DBDIR%\%cqmname%.fdb >> %FBDIR%\aliases.conf
:EXIST_ALIAS
echo     ok.

echo ���� ���� ������ %cqmname%...
if exist %DBDIR%\%cqmname%.fdb goto EXIST_DB_FILE
echo     �� �����.

echo ����⪠ ����⠭����� �� १�ࢭ�� �����...
call %CQMDIR%\lib\dbservice\restore.cmd
if %errorlevel% NEQ 0 (
	echo     �����襭�� � �訡���.
	) else goto EXIST_DB_FILE

echo �������� ���� ������...
%FBDIR%\bin\gbak.exe -C -user %FB_SCRIPT_USER% -password %FB_SCRIPT_PASS% %CQMDIR%\lib\sql\cqm.fbk %cqmname%
echo ��砫쭮� ���������� ���� ������...
%FBDIR%\bin\isql.exe -quiet -input %CQMDIR%\lib\sql\start_fill_%cqmname%.sql
if %errorlevel% NEQ 0 echo     �����襭�� � �訡���.


:EXIST_DB_FILE
echo     ok.


:STEP_5
echo.
echo.
echo ��� 5. ��⠭���� �ࠩ��� �����/�뢮��.
echo ----------------------------------------
%CQMDIR%\lib\winio\install i

echo.
echo.
echo ��� 6. ����ன�� ���㦥���.
echo ----------------------------------------
echo ��모...
xcopy %CQMDIR%\lib\links "%ALLUSERSPROFILE%\" /f /y /s /e /q
if exist %CQMDIR%\..\nshell\bin\nshell.exe xcopy %CQMDIR%\lib\nshell %CQMDIR%\..\nshell\etc\ /y /s /e /q

echo ��४�ਨ ��� १�ࢨ஢����...
if not exist c:\backup                mkdir c:\backup
xcopy .\infitis\cqm\log c:\backup\log\ /y /s /e /q
if not exist d:\backup mkdir d:\backup

echo �����祭�� ������� �� �ᯨᠭ��...
at 00:20 /interactive /every:M,T,W,Th,F,S,Su %CQMDIR%\bin\everyday.exe
at 00:15 /interactive /every:Th %CQMDIR%\bin\everyweek.exe
at 00:10 /interactive /every:M,T,W,Th,F,S,Su %CQMDIR%\bin\backupdb.exe
at 12:10 /interactive /every:M,T,W,Th,F,S,Su %CQMDIR%\bin\backupdb.exe
echo ��⮫����...
pushd %CQMDIR%\lib\autologin
rem call enable.cmd
autologin.reg
popd

echo.
echo.
echo        ���⠫���� �����襭�.
echo ----------------------------------------
echo.
echo �����⥫쭮 ४�����㥬 ������������� ��⥬�.
pause

:THE_END
echo ���筮� ࠡ���!
