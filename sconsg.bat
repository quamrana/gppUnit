rem sconsg.bat
@echo off
echo Building...
call sconsq.bat cov=gcov
echo running gcov...
call all-gcov.bat
echo running summ-gcov.py...
python summ-gcov.py
