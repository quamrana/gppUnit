@echo off
rem build with coverage
echo %time%
call jruntests.bat -j 8
echo %time%
call jplot-gcov
echo %time%
