@echo off
rem ---------------------------------------------
rem Скрипт для создания инсталляхи по мку.
rem Версия 3.0
rem (с) 2004 Руслан Кеба, 2006 Инфитис
rem ---------------------------------------------

echo Создание инсталятора МКУ
if "%1" EQU "" (
    echo Не понял для кого делаем инсталляху.
    goto BYE
    )
if not exist .\%1 (
    echo Нет такого объекта.
    goto BYE
    )

echo Создание инсталятора МКУ [%1]

echo Создание временной директории.
mkdir _create_inst_%1

echo Копирование независимых файлов.
xcopy .\_install\* .\_create_inst_%1 /y /e /s

echo Копирование свежих exe, dll и php.
xcopy ..\server\cqmsrv.exe          .\_create_inst_%1\infitis\cqm\bin\            /y
xcopy ..\client\cqmcli.exe          .\_create_inst_%1\infitis\cqm\bin\            /y
xcopy ..\doc\about\about.rtf        .\_create_inst_%1\infitis\cqm\doc\about\      /y
xcopy ..\lib\autologin              .\_create_inst_%1\infitis\cqm\lib\autologin\  /y /s /e
xcopy ..\lib\enter                  .\_create_inst_%1\infitis\cqm\lib\enter\      /y /s /e
mkdir .\_create_inst_%1\infitis\cqm\lib\ext
xcopy ..\lib\ext\%1\*.dll           .\_create_inst_%1\infitis\cqm\lib\ext\        /y
xcopy ..\lib\job                    .\_create_inst_%1\infitis\cqm\lib\job\        /y /s /e
xcopy ..\lib\dbservice              .\_create_inst_%1\infitis\cqm\lib\dbservice\  /y /s /e
xcopy ..\lib\links                  .\_create_inst_%1\infitis\cqm\lib\links\      /y /s /e
xcopy ..\lib\nshell                 .\_create_inst_%1\infitis\cqm\lib\nshell\     /y /s /e
xcopy ..\lib\maxima                 .\_create_inst_%1\infitis\cqm\lib\maxima\     /y /s /e
xcopy ..\lib\scilab                 .\_create_inst_%1\infitis\cqm\lib\scilab\     /y /s /e
xcopy ..\lib\scripts                .\_create_inst_%1\infitis\cqm\lib\scripts\    /y /s /e
xcopy ..\lib\sql                    .\_create_inst_%1\infitis\cqm\lib\sql\        /y /s /e
xcopy ..\lib\testio                 .\_create_inst_%1\infitis\cqm\lib\testio\     /y /s /e
xcopy ..\lib\util                   .\_create_inst_%1\infitis\cqm\lib\util\       /y /s /e
xcopy ..\lib\winio                  .\_create_inst_%1\infitis\cqm\lib\winio\      /y /s /e

echo Копирование fbbu
xcopy ..\..\fbbu                    .\_create_inst_%1\infitis\db\fbbu\            /y /s /e

echo Копирование локально-зависимых файлов.
xcopy .\%1\*   .\_create_inst_%1\infitis\ /y /e /s

echo Создание полного cqmname.cmd
copy .\_create_inst_%1\infitis\cqm\bin\cqmname.cmd + .\_create_inst_%1\infitis\cqm\bin\cqmvars.cmd .\_create_inst_%1\infitis\cqm\bin\cqmname.cmd

echo База данных
pushd .\_create_inst_%1\infitis\cqm\lib\scripts\mkdb
call mkdb.cmd
popd

echo Создание инсталляционного архива.
del *.7z
cd _create_inst_%1
7za a -t7z -mx=9 -y -r ..\infitis.7z
cd ..
copy /b "c:\Program Files\arc\bin\7zSD.sfx" + _util\sfx.conf + infitis.7z inst_cqm_[%1].exe
del *.7z
xcopy inst_cqm_[%1].exe \\lab\projects\MKU\builds\ /y

echo Удаление временной директории.
rmdir _create_inst_%1 /s /q

echo Готово.
:BYE
echo Приятной работы.
