@echo off
cppcheck --version
cppcheck --enable=all --inconclusive --suppressions-list=suppressions.txt --quiet -j 8 --template vs src Matchers TableFormatting 2>&1 | find /V "cppcheck: unusedFunction check"
rem cppcheck --enable=all --inconclusive --suppressions-list=blank.txt --xml-version=2 --quiet --template vs src Matchers TableFormatting 2>&1
