@echo off
rem ��ਯ� ࠧ�뢠 ᮥ�������
rem hang.cmd <��ꥪ�> <ᮥ�������>

if "%2" equ "" goto NOPARAMS
      
echo.
echo    ��� ���業��
echo    ��ꥪ�: %1
echo.
echo    ����� ᮥ�������
echo.

rasdial %2 /D
set exitcode=%errorlevel%

..\cmd\apause.exe 5
exit %exitcode%

:NOPARAMS
echo    �訡��: �������筮 ��ࠬ��஢.
exit 1
