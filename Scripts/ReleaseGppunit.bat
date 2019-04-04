@echo off
@echo Release gppUnit

xcopy Debug\gppUnit.lib* Released\vs2017\gppUnit1.5\lib /I /Q /Y
xcopy Debug\*.pdb Released\vs2017\gppUnit1.5\lib /I /Q /Y

xcopy Matchers\*.h Released\vs2017\gppUnit1.5\include\Matchers /I /Q /Y
xcopy ApprovalsTest\*.h Released\vs2017\gppUnit1.5\include\ApprovalsTest /I /Q /Y
xcopy TableFormatting\*.h Released\vs2017\gppUnit1.5\include\TableFormatting /I /Q /Y
xcopy src\*.h Released\vs2017\gppUnit1.5\include\gppUnit /I /Q /Y
