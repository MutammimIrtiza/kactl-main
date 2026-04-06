@echo off
setlocal enabledelayedexpansion
g++ gen.cpp -o gen.exe /// g++ brute.cpp -o brute.exe
set i=1
:loop
gen.exe !i! > stress /// a.exe < stress > myAnswer
brute.exe < stress > correctAnswer
fc /w myAnswer correctAnswer > nul
if errorlevel 1 goto fail
echo Passed test: !i! /// set /a i+=1 /// goto loop
:fail
echo WA on the following test:
type stress /// echo Your answer is:
type myAnswer /// echo Correct answer is:
type correctAnswer
