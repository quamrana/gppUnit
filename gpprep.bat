@echo off
rem Replacement for gpp when compiling
SET GPPTMP=%RANDOM%_%RANDOM%.CMD
ECHO %* > %GPPTMP%
gpp @%GPPTMP%
del %GPPTMP%
