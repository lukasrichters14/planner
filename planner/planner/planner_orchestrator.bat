@echo off

IF "%1"=="init" GOTO init

	:: Write quickstart output to a temp file.
	python C:\Users\lukas\planner\planner\planner\quickstart.py > p_orch_temp.txt

	:: Read quickstart output from temp file and delete temp file.
	set /p api_out= < p_orch_temp.txt
	del p_orch_temp.txt

	:: Call planner program.
	C:\Users\lukas\planner\planner\Debug\planner.exe %api_out%

	goto:eof


:init 
	C:\Users\lukas\planner\planner\Debug\planner.exe %1