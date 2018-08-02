@echo off
rem usage:  store 3.0.2

echo Cqm Source Saver
if "%1" NEQ "" goto NEXT_0
echo VERSION not defined.
goto BYE

:NEXT_0
set CQM_SOURCE_VERSION=%1

.\lib\store\curdate.cphp
call curdate.cmd
del curdate.cmd

if "%CQM_SOURCE_DATE%" NEQ "" goto NEXT_1
echo VERSION not defined.
goto BYE

:NEXT_1
echo     version  is %CQM_SOURCE_VERSION%
echo     date     is %CQM_SOURCE_DATE%

pushd ..
if exist cqm-%CQM_SOURCE_VERSION% (
    echo cqm-%CQM_SOURCE_VERSION% already exists!
    popd
    goto ZIP
)

popd
mkdir ..\cqm-%CQM_SOURCE_VERSION%
xcopy .\* ..\cqm-%CQM_SOURCE_VERSION%\ /s /e /q /exclude:.\lib\store\exclude_copy.txt

:ZIP

echo cqm-%CQM_SOURCE_VERSION%\* > ..\cqm-%CQM_SOURCE_VERSION%\lib\store\include_arch.txt
echo fbbu\*                    >> ..\cqm-%CQM_SOURCE_VERSION%\lib\store\include_arch.txt
set SRC_FILE=cqm-%CQM_SOURCE_VERSION%.%CQM_SOURCE_DATE%.7z
echo     filename is %SRC_FILE%

pushd ..
7za.exe a -t7z -mx=9 -y -r -pquadrangularPIRAMYD -x@.\cqm-%CQM_SOURCE_VERSION%\lib\store\exclude_arch.txt %SRC_FILE% @.\cqm-%CQM_SOURCE_VERSION%\lib\store\include_arch.txt
cqm-%CQM_SOURCE_VERSION%\lib\util\linkd.exe cqm-3 cqm-%CQM_SOURCE_VERSION%
popd

xcopy ..\%SRC_FILE% d:\store\mku\ /y
xcopy ..\%SRC_FILE% \\kometalab\projects\MKU\sources\ /y
xcopy ..\%SRC_FILE% e:\store\mku\ /y
del   ..\%SRC_FILE%



:BYE
echo bye.
