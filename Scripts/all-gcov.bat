@echo off
rem all-gcov
gcov --version  | find "gcov"

gcov -r -m src\*.cpp Matchers\*.cpp TableFormatting\*.cpp ApprovalsTest\*.cpp test\*.cpp 2>&1 | grep "xyz"
