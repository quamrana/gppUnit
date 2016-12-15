@echo off
astyle --version
astyle --options=astyle.options src\*.cpp src\*.h Matchers\*.cpp Matchers\*.h TableFormatting\*.cpp TableFormatting\*.h test\*.cpp test\*.h | find "Formatted"
