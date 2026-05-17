@echo off

if exist "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" (
    call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
    cl /EHsc /std:c++17 /Fe:calculator.exe src/main.cpp src/Calculator.cpp
    goto done
)

if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
    cl /EHsc /std:c++17 /Fe:calculator.exe src/main.cpp src/Calculator.cpp
    goto done
)

if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" (
    call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
    cl /EHsc /std:c++17 /Fe:calculator.exe src/main.cpp src/Calculator.cpp
    goto done
)

echo ERROR: Compiler not found.
pause
exit /b 1

:done
if exist calculator.exe (
    echo.
    echo SUCCESS! Run: calculator.exe
) else (
    echo BUILD FAILED. See errors above.
)
pause
