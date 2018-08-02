@echo off
if "%1" NEQ "" goto NEXT_0
echo Не понял для какого объета копируем.
goto BYE
:NEXT_0

echo Копирование конфигурации объекта [%1] из remote для отладки.

xcopy ..\objects\%1\cqm\etc\* ..\etc /y

echo Отключение поверки питания.
pushd ..\lib\util
disable_checkpower.cphp
popd

echo Готово.
:BYE
echo Приятной работы.
