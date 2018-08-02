@echo off
call cqmname.cmd
pushd %DBSDIR%
call rs.cmd %cqmname%
set exitcode=%errorlevel%
popd
exit /b %exitcode%
