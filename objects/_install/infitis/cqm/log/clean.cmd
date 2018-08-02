for /D %%i in (".\*" ) do (
	cd %%i
	call clean.cmd
	cd ..
)




