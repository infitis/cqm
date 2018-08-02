@echo off
echo �������� ���⠫��� ��� �����㬥�⮢.

echo �������� �६����� ��४�ਨ.
mkdir __tmp

echo ����஢���� ������ᨬ�� 䠩���.
xcopy .\_inst\* .\__tmp /y /e /s

echo ����஢���� ����ᨬ�� 䠩���.
for /D %%i in (".\*.tool") do (
    xcopy %%i\*.exe __tmp\infitis\cqm\bin\ /y /e /s
    xcopy %%i\*.txt __tmp\infitis\cqm\doc\tools\ /y /e /s
)

echo �������� ���⠫��樮����� ��娢�.
del *.7z
del inst_infitis_cqm_tools.exe
cd __tmp
7za a -t7z -mx=9 -y -r ..\infitis_cqm_tools.7z
cd ..
copy /b "c:\Program Files\arc\bin\7zSD.sfx" + _util\sfx.conf + infitis_cqm_tools.7z inst_cqm_tools.exe
del *.7z

echo �������� �६����� ��४�ਨ.
rmdir __tmp /s /q

echo ������㥬 �� �ࢥ�.
xcopy inst_infitis_cqm_tools.exe \\kometalab\projects\mku\builds /y

echo ��⮢�.
:BYE
echo ���⭮� ࠡ���.
