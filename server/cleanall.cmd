del logs\*.log
del signals\*.csv
for %%i in ("*.obj" "*.tds" "*.exe" "*.~*" "*.mb*" "*.il*") do del %%i
cd ..\common\classes
for %%i in ("*.obj" "*.tds" "*.exe" "*.~*" "*.mb*" "*.il*") do del %%i
cd ..\windows
for %%i in ("*.obj" "*.tds" "*.exe" "*.~*" "*.mb*" "*.il*") do del %%i
cd ..\client
for %%i in ("*.obj" "*.tds" "*.exe" "*.~*" "*.mb*" "*.il*") do del %%i
cd ..\..\server
