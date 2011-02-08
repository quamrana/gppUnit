@echo off
rem all-gcov
for %%d in (Matchers src src\djgpp TableFormatting test) do for %%f IN (%%d\*.cpp) do call run-gcov.bat %%d %%f
