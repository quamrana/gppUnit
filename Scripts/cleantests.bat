@echo off
python D:\scons-local-3.0.1\scons.py -c %* -f SConstruct --silent compiler=mingw
clean-gcov.py
