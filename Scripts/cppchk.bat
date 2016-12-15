@echo off
cppcheck --version
cppcheck --enable=all --inconclusive --suppressions-list=suppressions.txt --quiet -j 8 -I . -I .\src -I .\Matchers -I .\TableFormatting --template vs src Matchers TableFormatting 2>&1 | find /V "cppcheck: unusedFunction check"
rem cppcheck --enable=all --inconclusive --suppressions-list=suppressions.txt --xml-version=2 --quiet -I . -I .\src -I .\Matchers -I .\TableFormatting --template vs src Matchers TableFormatting 2>&1

rem cppcheck --check-config --enable=all --inconclusive --suppressions-list=blank.txt --quiet -j 8 -I . -I .\src -I .\Matchers -I .\TableFormatting --template vs src Matchers TableFormatting

