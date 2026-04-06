@echo off /// set SRC=code.cpp /// set EXE=a
g++ -std=c++17 -DLOCAL -Wshadow -Wall -g -D_GLIBCXX_DEBUG -fmax-errors=2 %SRC% -o %EXE%
if errorlevel 1 (
    echo Compilation failed! /// exit /b
)
echo. /// echo Input: /// type %1 /// echo.
echo. /// echo Output: /// %EXE% < %1 /// echo.
/// alt : gnu++14  or ++11 or ++1z