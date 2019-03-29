@echo off
astyle3 --version
astyle3 --options=astyle.options src\*.cpp src\*.h Matchers\*.cpp Matchers\*.h TableFormatting\*.cpp TableFormatting\*.h ApprovalsTest\*.cpp ApprovalsTest\*.h test\*.cpp test\*.h | find "Formatted"
