@echo off
rem ��ਯ� ���⠫��樨 ��� �����㬥�⮢.
rem ����� 1.0 ��� Windows 2000/XP.
rem (C) 2006 �����.
echo.
echo.
echo ----------------------------------------
echo     ���⠫���� ��� �����㬥�⮢
echo ----------------------------------------
echo.
echo.
echo.
echo.
echo     ����஢���� 䠩���.
echo ----------------------------------------
xcopy .\infitis c:\infitis\ /y /s /e /q
echo     ok.
echo.
echo.
echo.
echo.
echo     ����ன�� ��몮�.
echo ----------------------------------------
xcopy .\infitis\cqm\lib\links "%ALLUSERSPROFILE%\������� ����\�ணࠬ��\" /y /s /e /q
if exist c:\infitis\nshell\bin\nshell.exe xcopy .\infitis\cqm\lib\nshell c:\infitis\nshell\etc\ /y /s /e /q
echo     ok.
echo.
echo.
echo.
echo.
echo     ���⠫���� �����襭�.
echo ----------------------------------------
echo.
echo.
echo.
echo.
echo     ���筮� ࠡ���!
pause

:THE_END
