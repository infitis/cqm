@echo off
rem скрипт, который запускается для резервирования базы данных

rem моё имя
call cqmname.cmd

echo. >> ..\..\log\job\backupdb.log
echo. >> ..\..\log\job\backupdb.log
echo. >> ..\..\log\job\backupdb.log
echo =================================== >> ..\..\log\job\backupdb.log
echo %DATE% %TIME% >> ..\..\log\job\backupdb.log

call ..\dbservice\backup.cmd >> ..\..\log\job\backupdb.log 2>&1


if "%FLASH_BACKUP%" NEQ "" (
    if not exist %FLASH_BACKUP% (
        echo error: FLASH_BACKUP = '%FLASH_BACKUP%' not exist >> ..\..\log\job\backupdb.log
        goto END_FLASH_BACKUP
    )
    xcopy %DBDIR%\backup\%cqmname%.fbk.gz %FLASH_BACKUP%\ /y /q >NUL
)

:END_FLASH_BACKUP