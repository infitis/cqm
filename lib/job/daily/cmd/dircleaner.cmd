@echo off

call cqmname.cmd

echo dircleaner.cphp %CQMDIR%\log\client log 1 %LOGBUDIR%\client
..\scripts\common\dircleaner.cphp %CQMDIR%\log\client log 1 %LOGBUDIR%\client
echo dircleaner.cphp %CQMDIR%\log\server log 1 %LOGBUDIR%\server
..\scripts\common\dircleaner.cphp %CQMDIR%\log\server log 1 %LOGBUDIR%\server
echo dircleaner.cphp %CQMDIR%\log\signal log 1 %LOGBUDIR%\signal
..\scripts\common\dircleaner.cphp %CQMDIR%\log\signal csv 1 %LOGBUDIR%\signal

echo dircleaner.cphp %LOGBUDIR%\client   gz  45
..\scripts\common\dircleaner.cphp %LOGBUDIR%\client   gz  45
echo dircleaner.cphp %LOGBUDIR%\server   gz  45
..\scripts\common\dircleaner.cphp %LOGBUDIR%\server   gz  45
echo dircleaner.cphp %LOGBUDIR%\signal   gz  45
..\scripts\common\dircleaner.cphp %LOGBUDIR%\signal   gz  45

rem db backups
call %DBDIR%\fbbu\vars.cmd

echo dircleaner.cphp %FBBUDIR1% gz  60
..\scripts\common\dircleaner.cphp %FBBUDIR1% gz  60

echo dircleaner.cphp %FBBUDIR2% gz  60
..\scripts\common\dircleaner.cphp %FBBUDIR2% gz  60

echo dircleaner.cphp %FBBUDIR3% gz  60
..\scripts\common\dircleaner.cphp %FBBUDIR3% gz  60

echo dircleaner.cphp %FBBUDIR4% gz  60
..\scripts\common\dircleaner.cphp %FBBUDIR4% gz  60
