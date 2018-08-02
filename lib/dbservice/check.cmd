@echo off
call cqmname.cmd
pushd %DBSDIR%
call ch.cmd %cqmname%
set exitcode=%errorlevel%
popd
exit /b %exitcode%
