@echo off
rem -----------------------------------------------------------------
rem ��ਯ� �����⠫��樨 �ணࠬ����� ���ᯥ祭�� �������� ���
rem ����� 3.0 ��� Windows 2000/XP
rem Copyright (C) 2004 ��᫠� ����, 2006 �����
rem -----------------------------------------------------------------

echo.
echo.
echo ----------------------------------------
echo     �����⠫���� �� �������� ���
echo ----------------------------------------
echo.
echo.
echo ��������!
echo ��� �믮������ �����⠫��樨 �� ��� 㡥�����, �� :
echo * ��� ��ࢥ�
echo * ��� ������
echo �� ��������.
echo.
pause

call cqmname.cmd

echo.
echo.
echo ��� 6. �������� ���㦥���.
echo ----------------------------------------
echo ��모...
del "%ALLUSERSPROFILE%\������� ����\�ணࠬ��\��⮧���㧪�\*���*.lnk" /q
del "%ALLUSERSPROFILE%\����稩 �⮫\���*.lnk" /q
rmdir "%ALLUSERSPROFILE%\������� ����\�ணࠬ��\����� ���" /s /q
del "%ALLUSERSPROFILE%\������� ����\*��������.lnk" /q
echo �����祭�� �������...
at /delete /yes
echo �⪫�祭�� ��⮫�����...
pushd %CQMDIR%\lib\autologin
call disable.cmd
popd
echo     ok.


echo.
echo.
echo ��� 5. �������� �ࠩ��� �����/�뢮��.
echo ----------------------------------------
echo ��������...
%CQMDIR%\lib\winio\install r
echo     ok.


echo.
echo ��� 4. ���� ������
echo ----------------------------------------
echo �������� १�ࢭ�� �����...
call %CQMDIR%\lib\dbservice\backup.cmd
echo     ok.


echo.
echo.
echo ��� 3. �������� 䠩��� �� ����.
echo ----------------------------------------
rmdir %CQMDIR%\bin /s /q
rmdir %CQMDIR%\etc /s /q
rmdir %CQMDIR%\doc /s /q
rmdir %CQMDIR%\lib /s /q
del   %windir%\system32\cqmname.cmd /q
echo     ok.


echo.
echo ��� 2. �஢�ઠ �������� php
echo ----------------------------------------
echo.
echo     �ய�饭.


echo.
echo ��� 1. �஢�ઠ �ࢥ� Firebird
echo ----------------------------------------
echo.
echo     �ய�饭.


echo.
echo     �����⠫���� �����襭�.
echo ----------------------------------------
echo.
echo �ᥣ� ���ண�!
pause
rem suicide
rmdir %CQMDIR%\uninst /s /q
