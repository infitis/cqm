@echo off
if "%1" NEQ "" goto NEXT_0
echo �� ���� ��� ������ ���� �����㥬.
goto BYE
:NEXT_0

echo ����஢���� ���䨣��樨 ��ꥪ� [%1] �� remote ��� �⫠���.

xcopy ..\objects\%1\cqm\etc\* ..\etc /y

echo �⪫�祭�� ����ન ��⠭��.
pushd ..\lib\util
disable_checkpower.cphp
popd

echo ��⮢�.
:BYE
echo ���⭮� ࠡ���.
