@echo off
echo.
echo     旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
echo     �                                       �
echo     �  럣늻�뜄� ��룗몜� 뙄� 몗릠뀗�...      �
echo     �                                       �
echo     읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
echo.
..\lib\util\waitsemaphore.exe cqm_server_running_now_semaphore 4
if errorlevel 1 goto TIMEOUT
start /min cqmsrv.exe
goto BYE

:TIMEOUT
cls
echo.
echo     旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
echo     �                                       �
echo     �  뙄� 몗릠뀗 뱠� ��걥��뀙 !            �
echo     �                                       �
echo     읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
echo.

:BYE
..\lib\util\apause.exe 5
echo     ��룗솀�.
