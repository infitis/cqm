@echo off
call cqmname.cmd
pushd %DBSDIR%
call bu.cmd %cqmname%
set exitcode=%errorlevel%
popd
exit /b %exitcode%
