@echo off
rem -----------------------------------------------------------------
rem Скрипт деинсталляции программного обеспечения комплекса МКУ
rem Версия 3.0 для Windows 2000/XP
rem Copyright (C) 2004 Руслан Кеба, 2006 Инфитис
rem -----------------------------------------------------------------

echo.
echo.
echo ----------------------------------------
echo     Деинсталляция ПО комплекса МКУ
echo ----------------------------------------
echo.
echo.
echo ВНИМАНИЕ!
echo Для выполнения деинсталляции ПО МКУ убедитесь, что :
echo * МКУ Сервер
echo * МКУ Клиент
echo НЕ ЗАПУЩЕНЫ.
echo.
pause

call cqmname.cmd

echo.
echo.
echo ШАГ 6. Удаление окружения.
echo ----------------------------------------
echo Ярлыки...
del "%ALLUSERSPROFILE%\Главное Меню\Программы\Автозагрузка\*МКУ*.lnk" /q
del "%ALLUSERSPROFILE%\Рабочий Стол\МКУ*.lnk" /q
rmdir "%ALLUSERSPROFILE%\Главное Меню\Программы\Инфитис МКУ" /s /q
del "%ALLUSERSPROFILE%\Главное Меню\*компьютер.lnk" /q
echo Назначенные задания...
at /delete /yes
echo Отключение автологина...
pushd %CQMDIR%\lib\autologin
call disable.cmd
popd
echo     ok.


echo.
echo.
echo ШАГ 5. Удаление драйвера ввода/вывода.
echo ----------------------------------------
echo Удаление...
%CQMDIR%\lib\winio\install r
echo     ok.


echo.
echo ШАГ 4. База данных
echo ----------------------------------------
echo Создание резервной копии...
call %CQMDIR%\lib\dbservice\backup.cmd
echo     ok.


echo.
echo.
echo ШАГ 3. Удаление файлов ПО кМКУ.
echo ----------------------------------------
rmdir %CQMDIR%\bin /s /q
rmdir %CQMDIR%\etc /s /q
rmdir %CQMDIR%\doc /s /q
rmdir %CQMDIR%\lib /s /q
del   %windir%\system32\cqmname.cmd /q
echo     ok.


echo.
echo ШАГ 2. Проверка интерпретатора php
echo ----------------------------------------
echo.
echo     пропущен.


echo.
echo ШАГ 1. Проверка сервера Firebird
echo ----------------------------------------
echo.
echo     пропущен.


echo.
echo     Деинсталляция завершена.
echo ----------------------------------------
echo.
echo Всего доброго!
pause
rem suicide
rmdir %CQMDIR%\uninst /s /q
