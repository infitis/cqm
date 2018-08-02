@echo off
rem Скрипт установки соединения
rem dial.cmd <объект> <соединение> <пользователь> <пароль> <номер телефона>

if "%5" equ "" goto NOPARAMS
      
echo.
echo    МКУ Инфоцентр
echo    Объект: %1
echo.
echo    Установка соединения
echo.

rasdial %2 %3 %4 /PHONE:%5      
set exitcode=%errorlevel%

..\cmd\apause.exe 5
exit %exitcode%

:NOPARAMS
echo    Ошибка: Недостаточно параметров.
exit 1
