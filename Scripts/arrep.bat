@echo off
rem Replacement for ar
SET ARTMP=%RANDOM%_%RANDOM%.CMD
ECHO %* > %ARTMP%
ar @%ARTMP%
del %ARTMP%
