@echo off
rem ��ਯ� ���������� ���� ������
rem update.cmd <��ꥪ�> <�.���> <�.���� ������> <�.���짮��⥫�> <������ ����������> <�.��஫�>

if "%5" equ "" goto NOPARAMS
set pswd=
if not "%6" equ "" set pswd=--password=%6
      
echo.
echo    ��� ���業��
echo    ��ꥪ�: %1
echo.
echo    ���������� ���� ������
echo.
echo.
echo    ��� 1. ����祭�� ������ � ��ꥪ�.
c:\mysql\bin\mysqldump.exe --host=%2 --user=%4 %pswd% --compress --no-create-db --no-create-info "--where=moment>='%5' order by moment" --result-file=..\sql\update_%3.sql %3 points routes vagons accumulators
set exitcode=%errorlevel%
if not %exitcode% equ 0 goto BADEXITCODE
echo.
echo.
echo    ��� 2. �����⮢�� ������
..\cmd\replace.php ..\sql\update_%3.sql INSERT REPLACE
set exitcode=%errorlevel%
if not %exitcode% equ 0 goto BADEXITCODE
echo.
echo.
echo    ��� 3. �ਬ������ ������ �� �����쭮� ��������.
c:\mysql\bin\mysql --host=localhost --user=root --database=%3 --force < ..\sql\update_%3.sql 2>&3
set exitcode=%errorlevel%
if not %exitcode% equ 0 goto BADEXITCODE

..\cmd\apause 5
exit %exitcode%

:NOPARAMS
echo    �訡��: �������筮 ��ࠬ��஢.
..\cmd\apause 5
exit 1

:BADEXITCODE
echo    �訡�� ���������� ���� ������.
echo    ��� = %exitcode%
..\cmd\apause 5
exit %exitcode%
