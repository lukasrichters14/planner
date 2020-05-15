@echo off

:: File Locations
set python_location = C:\Users\lukas\AppData\Local\Programs\Python\Python37\python.exe
set api_script = C:\Users\lukas\planner\planner\planner\quickstart.py
set planner_script = C:\Users\lukas\planner\planner\Debug\planner.exe

:: Run program
python %api_script% | %planner_script%