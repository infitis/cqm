@echo off
rem ��ਯ� १�ࢨ஢���� ���� ������
rem backup.cmd <��ꥪ�> <���� ������> <��४��� ��� �����>

if "%3" equ "" goto NOPARAMS
      
echo.
echo    ��� ���業��
echo    ��ꥪ�: %1
echo.
echo    ����ࢨ஢���� ���� ������
echo    ��४��� ��� १�ࢠ: %3
echo.
echo.
..\magula\mbu.php %2 -b%3

set exitcode=%errorlevel%
if not %exitcode% equ 0 goto BADEXITCODE

..\cmd\apause 5
exit %exitcode%

:NOPARAMS
echo    �訡��: �������筮 ��ࠬ��஢.
..\cmd\apause 5
exit 1

:BADEXITCODE
echo    �訡�� १�ࢨ஢���� ���� ������.
echo    ��� = %exitcode%
..\cmd\apause 5
exit %exitcode%
