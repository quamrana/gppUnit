@echo off
rem all-gcov
for %%d in (Matchers src TableFormatting) do for %%f IN (%%d\*.cpp) do call run-gcov.bat %%d %%f
del .\gcov\*.gcov
move *.gcov .\gcov