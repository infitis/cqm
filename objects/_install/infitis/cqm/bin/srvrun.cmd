@echo off
echo.
echo     ���������������������������������������Ŀ
echo     �                                       �
echo     �  �������� ������� ��� �������...      �
echo     �                                       �
echo     �����������������������������������������
echo.
..\lib\util\waitsemaphore.exe cqm_server_running_now_semaphore 4
if errorlevel 1 goto TIMEOUT
start /min cqmsrv.exe
goto BYE

:TIMEOUT
cls
echo.
echo     ���������������������������������������Ŀ
echo     �                                       �
echo     �  ��� ������ ��� �������� !            �
echo     �                                       �
echo     �����������������������������������������
echo.

:BYE
..\lib\util\apause.exe 5
echo     �������.
