@echo off
echo Building and Running Tests

gcc --version | find "gcc"
rem call compilezlib.bat
python D:\scons-local-3.0.1\scons.py -f SConstruct -Q compiler=mingw cov=gcov %*

IF ERRORLEVEL 1 GOTO QUIT

rem run unit tests
@echo ------------------------------------
if not exist test\test.exe GOTO QUIT
PUSHD test
test  -m="D:\Program Files\Tortoise\TortoiseMerge.exe"
POPD

:QUIT
