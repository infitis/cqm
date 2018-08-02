@echo off
rem Скрипт инсталляции МКУ Инструментов.
rem Версия 1.0 для Windows 2000/XP.
rem (C) 2006 Инфитис.
echo.
echo.
echo ----------------------------------------
echo     Инсталляция МКУ Инструментов
echo ----------------------------------------
echo.
echo.
echo.
echo.
echo     Копирование файлов.
echo ----------------------------------------
xcopy .\infitis c:\infitis\ /y /s /e /q
echo     ok.
echo.
echo.
echo.
echo.
echo     Настройка ярлыков.
echo ----------------------------------------
xcopy .\infitis\cqm\lib\links "%ALLUSERSPROFILE%\Главное Меню\Программы\" /y /s /e /q
if exist c:\infitis\nshell\bin\nshell.exe xcopy .\infitis\cqm\lib\nshell c:\infitis\nshell\etc\ /y /s /e /q
echo     ok.
echo.
echo.
echo.
echo.
echo     Инсталляция завершена.
echo ----------------------------------------
echo.
echo.
echo.
echo.
echo     Удачной работы!
pause

:THE_END
