@echo off
echo Running jplot-gcov
clean-gcov.py .gcov
call all-gcov.bat
echo %time%
summ-gcov.py p
