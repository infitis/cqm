@echo off
for /D %%d in ("*") do (
echo directory %%d:
cd %%d
for %%i in ("*.obj" "*.tds" "*.exe" "*.~*" "*.mb*" "*.il*") do (
    echo               %%i
    del %%i
    )
cd ..
)
