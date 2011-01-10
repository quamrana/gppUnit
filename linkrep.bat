@echo off
rem Replacement for gpp when linking
SET LINKTMP=%RANDOM%_%RANDOM%.CMD
ECHO %* > %LINKTMP%
gpp @%LINKTMP%
del %LINKTMP%
