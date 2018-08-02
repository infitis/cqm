@echo off
rem Скрипт деинсталляции МКУ Инструментов.
rem Версия 1.0 для Windows 2000/XP.
rem (C) 2006 Инфитис.
echo.
echo.
echo ----------------------------------------
echo     Деинсталляция МКУ Инструментов
echo ----------------------------------------
echo.
echo.
echo.
echo.
echo     Удаление ярлыков.
echo ----------------------------------------
del "%ALLUSERSPROFILE%\Главное Меню\Программы\Инфитис МКУ\Инструменты" /s /q
if not exist "%ALLUSERSPROFILE%\Главное Меню\Программы\Инфитис МКУ\*.lnk" del "%ALLUSERSPROFILE%\Главное Меню\Программы\Инфитис МКУ" /s /q
echo     ok.
echo.
echo.
echo.
echo.
echo     Удаление файлов.
echo ----------------------------------------
rem Оставим файлы если есть сервер или клиент
if exist c:\infitis\cqm\bin\cqmsrv.exe goto THE_END
if exist c:\infitis\cqm\bin\cqmcli.exe goto THE_END
echo.
echo     Сейчас будет суицид...
echo     Удачной работы!
pause
rmdir  c:\infitis\cqm /s /q

:THE_END
echo     Деинсталляция завершена.
echo ----------------------------------------
echo.
echo.
echo.
echo.
echo     Удачной работы!
pause
