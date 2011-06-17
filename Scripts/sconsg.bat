@echo off

echo Building...
call sconsq.bat cov=gcov

echo running gcov...
python gcovr.py -o gcovr-summary.log -r . -e test
type gcovr-summary.log

@echo cleaning...
python clean-gcov.py
call sconsc.bat -s
