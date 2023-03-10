:LOOP
mingw32-make
main.exe
IF EXIST "dpipe_death" (
	GOTO DEATH
) ELSE (
	GOTO LOOP
)
:DEATH
del dpipe_death
