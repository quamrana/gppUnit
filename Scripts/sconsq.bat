@echo off

SET STARTBATCH=0
SET ENDBATCH=0
SET STARTBATCH=%TIME::=%

REM call scons -Q --debug=presub %*
call scons -Q -j 3 %*

rem run unit tests
IF ERRORLEVEL 1 GOTO QUIT

@echo ------------------------------------
if not exist test\test.exe GOTO QUIT
test\test

:QUIT
SET ENDBATCH=%TIME::=%

python print-time-diff.py
