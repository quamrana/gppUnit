@echo off
rem
AddLicense.py --version
AddLicense.py -f licence.txt src\*.cpp src\*.h Matchers\*.cpp Matchers\*.h TableFormatting\*.cpp TableFormatting\*.h ApprovalsTest\*.cpp ApprovalsTest\*.h
