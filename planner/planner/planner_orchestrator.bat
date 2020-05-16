@echo off

:: Run quickstart and save to temp file.
python C:\Users\lukas\planner\planner\planner\quickstart.py > p_orch_temp.txt

:: Read from temp file and delete.
set /p api_out= < p_orch_temp.txt
del p_orch_temp.txt

:: Run planner program.
C:\Users\lukas\planner\planner\Debug\planner.exe %api_out%