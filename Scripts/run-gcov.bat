@echo off
rem run-gcov
echo gcov %1 %2
gcov -l -p -o %1 %2 >nul
rem gcov -l -p -o %1 %2 >nul 2>&1
