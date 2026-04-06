@echo off
for %%f in (in1 in2 in3 in4 in5 in6 in7 in8 in9) do (
    if exist %%f (
        echo. /// echo Input: %%f /// type %%f
        echo. /// echo Output: ///a.exe < %%f /// echo.
    )
)
