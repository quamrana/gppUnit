@echo off
astyle --version
astyle --options=astyle.options --exclude=test *.cpp *.h
