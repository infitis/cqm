@echo off
rem ��ਯ� ����⮭������� ���� ������ (��� ���� �믮������ sql-�ਯ�)
rem restore.cmd <��ꥪ�> <dump.sql.gz>

if "%2" equ "" goto NOPARAMS
      
echo.
echo    ��� ���業��
echo    ��ꥪ�: %1
echo.
echo    ����⠭������� ���� ������
echo.
echo.
..\magula\mexec.php %2

set exitcode=%errorlevel%
if not %exitcode% equ 0 goto BADEXITCODE

..\cmd\apause 5
exit %exitcode%

:NOPARAMS
echo    �訡��: �������筮 ��ࠬ��஢.
..\cmd\apause 5
exit 1

:BADEXITCODE
echo    �訡�� ����⮭������� ���� ������.
echo    ��� = %exitcode%
..\cmd\apause 5
exit %exitcode%
