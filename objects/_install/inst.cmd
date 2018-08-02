@echo off
rem -----------------------------------------------------------------
rem Скрипт инсталляции программного обеспечения комплекса МКУ
rem Версия 3.0 для Windows 2000/XP
rem Copyright (C) 2004 Руслан Кеба, 2006 Инфитис
rem -----------------------------------------------------------------

echo.
echo.
echo ----------------------------------------
echo     Инсталляция ПО комплекса МКУ
echo ----------------------------------------
echo.
echo.
echo ВНИМАНИЕ!
echo Для работы ПО МКУ необходимо, что бы были установлены:
echo * Сервер Firebird (версия 1.5.2 и выше), запущен как служба
echo * Интерпретатор PHP (cli) (версия 5.1.1 и выше)
echo.
pause

rem project name
echo.
echo ШАГ 0. Имя проекта (cqmname).
echo ----------------------------------------
echo Копирование файла...
xcopy .\infitis\cqm\bin\cqmname.cmd %windir%\system32 /f /y /q
echo     ok.
echo Запуск...
call cqmname.cmd
echo     ok.

rem firebird instalation
echo.
echo ШАГ 1. Проверка сервера Firebird
echo ----------------------------------------
echo Проверка fbserver.exe...
if not exist %FBDIR%\bin\fbserver.exe (
	echo     не найден.
	goto NO_FB
	)
echo     ok.
echo Проверка клиентской библиотеки...
if not exist %FBDIR%\bin\instclient.exe (
	echo     не найден instclient.exe
	goto NO_FB
	)
%FBDIR%\bin\instclient query fbclient
if %errorlevel% NEQ 0 (
	echo 	не найдена.
	goto NO_FB
	)
echo     ok.
echo Проверка службы...
for /f %%i in ('net start') do if "%%i" EQU "Firebird" (
	echo     ok.
	goto INSTALLED_FB
	)
echo     не запущена.

:NO_FB
echo.
echo.
echo         ДАЛЬНЕЙШАЯ ИНСТАЛЯЦИЯ НЕВОЗМОЖНА.
echo         Проверка Firebird не пройдена.
echo.
echo         Инсталяция прервана!
echo.
pause
goto THE_END

:INSTALLED_FB

rem php instalation
echo.
echo ШАГ 2. Проверка интерпретатора php
echo ----------------------------------------
echo Проверка ассоциаций .cphp и .php...
assoc .cphp
if %errorlevel% NEQ 0 goto NO_PHP
ftype php.cqm.script
if %errorlevel% NEQ 0 goto NO_PHP
echo     ok.

goto STEP_3

:NO_PHP
echo.
echo.
echo         ДАЛЬНЕЙШАЯ ИНСТАЛЯЦИЯ НЕВОЗМОЖНА.
echo         Проверка php не пройдена.
echo.
echo         Инсталяция прервана!
echo.
pause
goto THE_END


:STEP_3
echo.
echo.
echo ШАГ 3. Копирование файлов ПО кМКУ.
echo ----------------------------------------
xcopy .\infitis c:\infitis\ /f /y /s /e /q
echo     ok.


echo.
echo ШАГ 4. База данных
echo ----------------------------------------
echo Запись в aliases.conf...
for /F "eol=# delims== " %%i in (%FBDIR%\aliases.conf) do (
	if /i %%i EQU %cqmname% goto EXIST_ALIAS
	)	
echo     не найдена, добавление...
echo %cqmname%=%DBDIR%\%cqmname%.fdb >> %FBDIR%\aliases.conf
:EXIST_ALIAS
echo     ok.

echo Файл базы данных %cqmname%...
if exist %DBDIR%\%cqmname%.fdb goto EXIST_DB_FILE
echo     не наден.

echo Попытка восстановить из резервной копии...
call %CQMDIR%\lib\dbservice\restore.cmd
if %errorlevel% NEQ 0 (
	echo     завершенно с ошибкой.
	) else goto EXIST_DB_FILE

echo Создание базы данных...
%FBDIR%\bin\gbak.exe -C -user %FB_SCRIPT_USER% -password %FB_SCRIPT_PASS% %CQMDIR%\lib\sql\cqm.fbk %cqmname%
echo Начальное заполнение базы данных...
%FBDIR%\bin\isql.exe -quiet -input %CQMDIR%\lib\sql\start_fill_%cqmname%.sql
if %errorlevel% NEQ 0 echo     завершенно с ошибкой.


:EXIST_DB_FILE
echo     ok.


:STEP_5
echo.
echo.
echo ШАГ 5. Установка драйвера ввода/вывода.
echo ----------------------------------------
%CQMDIR%\lib\winio\install i

echo.
echo.
echo ШАГ 6. Настройка окружения.
echo ----------------------------------------
echo Ярлыки...
xcopy %CQMDIR%\lib\links "%ALLUSERSPROFILE%\" /f /y /s /e /q
if exist %CQMDIR%\..\nshell\bin\nshell.exe xcopy %CQMDIR%\lib\nshell %CQMDIR%\..\nshell\etc\ /y /s /e /q

echo Директории для резервирования...
if not exist c:\backup                mkdir c:\backup
xcopy .\infitis\cqm\log c:\backup\log\ /y /s /e /q
if not exist d:\backup mkdir d:\backup

echo Назначенные задания по расписанию...
at 00:20 /interactive /every:M,T,W,Th,F,S,Su %CQMDIR%\bin\everyday.exe
at 00:15 /interactive /every:Th %CQMDIR%\bin\everyweek.exe
at 00:10 /interactive /every:M,T,W,Th,F,S,Su %CQMDIR%\bin\backupdb.exe
at 12:10 /interactive /every:M,T,W,Th,F,S,Su %CQMDIR%\bin\backupdb.exe
echo Автологин...
pushd %CQMDIR%\lib\autologin
rem call enable.cmd
autologin.reg
popd

echo.
echo.
echo        Инсталляция завершена.
echo ----------------------------------------
echo.
echo Настоятельно рекомендуем ПЕРЕЗАГРУЗИТЬ систему.
pause

:THE_END
echo Удачной работы!
