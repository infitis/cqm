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
echo                      ok.
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
..\lib\util\apause.exe 4
exit

:BYE
echo     �������.
exit