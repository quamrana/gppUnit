@echo off
call setdjgppscons.bat

call scons -Q --debug=presub %*

rem run unit tests
IF ERRORLEVEL 1 GOTO QUIT

@echo .
test\test

:QUIT
