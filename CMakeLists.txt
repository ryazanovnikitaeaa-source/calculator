cmake_minimum_required(VERSION 3.14)
project(Calculator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- Основная программа ---
add_executable(calculator
    src/main.cpp
    src/Calculator.cpp
)

# --- Тесты ---
add_executable(tests
    tests/test_calculator.cpp
    src/Calculator.cpp
)

# Папка tests/ должна видеть заголовок doctest.h
target_include_directories(tests PRIVATE tests)

# Команда: cmake --build . && ctest
enable_testing()
add_test(NAME CalculatorTests COMMAND tests)
