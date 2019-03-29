@echo off
@echo REMOVING ALL LICENSE HEADERS
pause
AddLicense.py --version
AddLicense.py -r -f licence.txt src\*.cpp src\*.h Matchers\*.cpp Matchers\*.h TableFormatting\*.cpp TableFormatting\*.h ApprovalsTest\*.cpp ApprovalsTest\*.h
