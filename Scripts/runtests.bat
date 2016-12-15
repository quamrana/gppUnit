@echo off
@echo Compiling...

SET STARTBATCH=0
SET ENDBATCH=0
SET STARTBATCH=%TIME::=%


rem build test app
gcc --version | find "gcc"
call scons -Q compiler=mingw %*

IF ERRORLEVEL 1 GOTO QUIT

rem run unit tests
@echo ------------------------------------
if not exist test\test.exe GOTO QUIT
test\test

:QUIT
SET ENDBATCH=%TIME::=%

print-time-diff.py

