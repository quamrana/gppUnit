@echo off
@echo Release gppUnit

echo Copy vs2017 files
xcopy Debug\gppUnit.lib* Released\vs2017\gppUnit1.5\lib /I /Q /Y >nul 2>&1
xcopy Debug\*.pdb Released\vs2017\gppUnit1.5\lib /EXCLUDE:exclude_test_pdb /I /Q /Y >nul 2>&1

echo Copy header files
xcopy Matchers\*.h Released\vs2017\gppUnit1.5\include\Matchers /I /Q /Y >nul 2>&1
xcopy ApprovalsTest\*.h Released\vs2017\gppUnit1.5\include\ApprovalsTest /I /Q /Y >nul 2>&1
xcopy TableFormatting\*.h Released\vs2017\gppUnit1.5\include\TableFormatting /I /Q /Y >nul 2>&1
xcopy src\*.h Released\vs2017\gppUnit1.5\include\gppUnit /I /Q /Y >nul 2>&1

echo copy .a files
mkdir Released\mingw\temp >nul 2>&1
mkdir Released\mingw\lib >nul 2>&1
xcopy Released\vs2017\gppUnit1.5\include\*.* Released\mingw\include /S /E /I /Q /Y >nul 2>&1
xcopy src\lib*.a Released\mingw\temp /I /Q /Y >nul 2>&1
xcopy ApprovalsTest\lib*.a Released\mingw\temp /I /Q /Y >nul 2>&1
xcopy Matchers\lib*.a Released\mingw\temp /I /Q /Y >nul 2>&1
xcopy TableFormatting\lib*.a Released\mingw\temp /I /Q /Y >nul 2>&1

echo ar new combined .a
PUSHD Released\mingw\temp
ar -x libgppUnit1.5.a
ar -x libApprovalsTest.a
ar -x libMatchers.a
ar -x libTableFormatting.a
del libgppUnit.a >nul 2>&1
del libgppUnit.b >nul 2>&1
ar rc libgppUnit.a *.o
ranlib libgppUnit.a
del *.o
ren libgppUnit.a libgppUnit.b
del *.a
echo move new .a file
ren libgppUnit.b libgppUnit.a
move /Y libgppUnit.a ..\lib >nul 2>&1
POPD

rmdir Released\mingw\temp /Q /S
echo gppUnit in Released:
dir Released /b
