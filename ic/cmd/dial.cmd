@echo off
rem ��ਯ� ��⠭���� ᮥ�������
rem dial.cmd <��ꥪ�> <ᮥ�������> <���짮��⥫�> <��஫�> <����� ⥫�䮭�>

if "%5" equ "" goto NOPARAMS
      
echo.
echo    ��� ���業��
echo    ��ꥪ�: %1
echo.
echo    ��⠭���� ᮥ�������
echo.

rasdial %2 %3 %4 /PHONE:%5      
set exitcode=%errorlevel%

..\cmd\apause.exe 5
exit %exitcode%

:NOPARAMS
echo    �訡��: �������筮 ��ࠬ��஢.
exit 1
