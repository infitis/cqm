@echo off
echo Создание инсталятора МКУ Инструментов.

echo Создание временной директории.
mkdir __tmp

echo Копирование независимых файлов.
xcopy .\_inst\* .\__tmp /y /e /s

echo Копирование зависимых файлов.
for /D %%i in (".\*.tool") do (
    xcopy %%i\*.exe __tmp\infitis\cqm\bin\ /y /e /s
    xcopy %%i\*.txt __tmp\infitis\cqm\doc\tools\ /y /e /s
)

echo Создание инсталляционного архива.
del *.7z
del inst_infitis_cqm_tools.exe
cd __tmp
7za a -t7z -mx=9 -y -r ..\infitis_cqm_tools.7z
cd ..
copy /b "c:\Program Files\arc\bin\7zSD.sfx" + _util\sfx.conf + infitis_cqm_tools.7z inst_cqm_tools.exe
del *.7z

echo Удаление временной директории.
rmdir __tmp /s /q

echo Скопируем на сервер.
xcopy inst_infitis_cqm_tools.exe \\kometalab\projects\mku\builds /y

echo Готово.
:BYE
echo Приятной работы.
