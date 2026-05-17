@echo off

if exist "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" (
    call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
    cl /EHsc /std:c++17 /Fe:tests.exe /I tests tests/test_calculator.cpp src/Calculator.cpp
    goto run
)

if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
    cl /EHsc /std:c++17 /Fe:tests.exe /I tests tests/test_calculator.cpp src/Calculator.cpp
    goto run
)

if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" (
    call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
    cl /EHsc /std:c++17 /Fe:tests.exe /I tests tests/test_calculator.cpp src/Calculator.cpp
    goto run
)

echo ERROR: Compiler not found.
pause
exit /b 1

:run
if exist tests.exe (
    echo.
    tests.exe
) else (
    echo TEST BUILD FAILED. See errors above.
)
pause
