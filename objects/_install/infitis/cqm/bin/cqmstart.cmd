@echo off

call cqmname.cmd
cd %CQMDIR%\bin

rem check running apps
..\lib\util\waitsemaphore.exe cqm_server_running_now_semaphore
if errorlevel 1 (
    set RUNNING_SERVER=1
    ) else (
    set RUNNING_SERVER=0
    )

..\lib\util\waitsemaphore.exe cqm_client_running_now_semaphore
if errorlevel 1 (
    set RUNNING_CLIENT=1
    ) else (
    set RUNNING_CLIENT=0
    )

if %RUNNING_SERVER% EQU 1 goto START_APPS
if %RUNNING_CLIENT% EQU 1 goto START_APPS

rem �஢�ઠ ���� ������
echo.
echo     �������������������������������������������������Ŀ
echo     �                                                 �
echo     �  �������� ���� ������...                        �
echo     �                                                 �
echo     ���������������������������������������������������
echo.
call ..\lib\dbservice\check.cmd
if %errorlevel% EQU 0 goto DB_TEST_PASSED

echo.
echo     �������������������������������������������������Ŀ
echo     �                                                 �
echo     �  ��������!!!                                    �
echo     �                                                 �
echo     �  ���� ������ ��� ����������.                    �
echo     �                                                 �
echo     �  ��稭�� ���०����� ����� ����                �
echo     �  �����४⭮� �����襭�� ࠡ��� ��������.     �
echo     �                                                 �
echo     �  ��������� ����⠭����� ���� ������            �
echo     �  �� १�ࢭ�� �����?                            �
echo     �                                                 �
echo     �  ��� �������������� ����� �������� ������       �
echo     �  �� ��������� 12 ����� ������.                  �
echo     �                                                 �
echo     �  ��� ����⠭������� ������ ������� ENTER       �
echo     �  ��� �⬥�� ������ ������� ESC                 �
echo     �                                                 �
echo     ���������������������������������������������������
echo.
..\lib\util\getenter.exe
if %errorlevel% EQU 0 (
    rem ����⠭��������
	echo        �����. ��� �������������� ���� ������...
	echo.
    call ..\lib\dbservice\restore.cmd
    if %errorlevel% EQU 0 goto DB_TEST_PASSED else (
echo.
echo     �������������������������������������������������Ŀ
echo     �                                                 �
echo     �  ������������ ���� ������ �� �������.           �
echo     �                                                 �
echo     ���������������������������������������������������
echo.

    )
)
echo.
echo     �������������������������������������������������Ŀ
echo     �                                                 �
echo     �  ���������� ������ ����������.                  �
echo     �                                                 �
echo     ���������������������������������������������������
echo.
pause
exit 1	

:DB_TEST_PASSED

rem echo.
rem echo     �������������������������������������������������Ŀ
rem echo     �                                                 �
rem echo     �  ����������� ���� ������...                     �
rem echo     �                                                 �
rem echo     ���������������������������������������������������
rem echo.
rem call ..\lib\dbservice\optimize.cmd
    

:START_APPS
if %RUNNING_SERVER% EQU 0 (
echo.
echo     �������������������������������������������������Ŀ
echo     �                                                 �
echo     �  ������ ��� �������...                          �
echo     �                                                 �
echo     ���������������������������������������������������
echo.
start /min cqmsrv.exe
..\lib\util\apause.exe 5
)


if %RUNNING_CLIENT% EQU 0 (
echo.
echo     �������������������������������������������������Ŀ
echo     �                                                 �
echo     �  ������ ��� �������...                          �
echo     �                                                 �
echo     ���������������������������������������������������
echo.
start cqmcli.exe
..\lib\util\apause.exe 5
)

exit 0
