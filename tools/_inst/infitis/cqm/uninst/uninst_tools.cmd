@echo off
rem ��ਯ� �����⠫��樨 ��� �����㬥�⮢.
rem ����� 1.0 ��� Windows 2000/XP.
rem (C) 2006 �����.
echo.
echo.
echo ----------------------------------------
echo     �����⠫���� ��� �����㬥�⮢
echo ----------------------------------------
echo.
echo.
echo.
echo.
echo     �������� ��몮�.
echo ----------------------------------------
del "%ALLUSERSPROFILE%\������� ����\�ணࠬ��\����� ���\�����㬥���" /s /q
if not exist "%ALLUSERSPROFILE%\������� ����\�ணࠬ��\����� ���\*.lnk" del "%ALLUSERSPROFILE%\������� ����\�ணࠬ��\����� ���" /s /q
echo     ok.
echo.
echo.
echo.
echo.
echo     �������� 䠩���.
echo ----------------------------------------
rem ��⠢�� 䠩�� �᫨ ���� �ࢥ� ��� ������
if exist c:\infitis\cqm\bin\cqmsrv.exe goto THE_END
if exist c:\infitis\cqm\bin\cqmcli.exe goto THE_END
echo.
echo     ����� �㤥� ��樤...
echo     ���筮� ࠡ���!
pause
rmdir  c:\infitis\cqm /s /q

:THE_END
echo     �����⠫���� �����襭�.
echo ----------------------------------------
echo.
echo.
echo.
echo.
echo     ���筮� ࠡ���!
pause
