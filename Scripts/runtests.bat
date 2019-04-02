@echo off
@echo Compiling...

SET STARTBATCH=0
SET ENDBATCH=0
SET STARTBATCH=%TIME::=%


rem build test app
gcc --version | find "gcc"
python D:\scons-local-3.0.1\scons.py -Q compiler=mingw %*

IF ERRORLEVEL 1 GOTO QUIT

rem run unit tests
@echo ------------------------------------
if not exist test\test.exe GOTO QUIT
PUSHD test
test
POPD

:QUIT
SET ENDBATCH=%TIME::=%

print-time-diff.py

