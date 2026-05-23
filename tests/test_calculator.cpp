#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/Calculator.h"

// ==================== Базовые операции ====================

TEST_CASE("Простое сложение") {
    Calculator calc;
    CHECK(calc.calculate("2+3") == 5.0);
    CHECK(calc.calculate("0+0") == 0.0);
    CHECK(calc.calculate("100+200") == 300.0);
}

TEST_CASE("Простое вычитание") {
    Calculator calc;
    CHECK(calc.calculate("10-4") == 6.0);
    CHECK(calc.calculate("0-5") == -5.0);
}

TEST_CASE("Простое умножение") {
    Calculator calc;
    CHECK(calc.calculate("3*4") == 12.0);
    CHECK(calc.calculate("0*999") == 0.0);
    CHECK(calc.calculate("-2*5") == -10.0);
}

TEST_CASE("Простое деление") {
    Calculator calc;
    CHECK(calc.calculate("10/2") == 5.0);
    CHECK(calc.calculate("7/2") == doctest::Approx(3.5));
    CHECK(calc.calculate("-9/3") == -3.0);
}

// ==================== Приоритет операций ====================

TEST_CASE("Умножение выполняется раньше сложения") {
    Calculator calc;
    // 2 + 2*2 = 2 + 4 = 6, а не (2+2)*2 = 8
    CHECK(calc.calculate("2+2*2") == 6.0);
}

TEST_CASE("Деление выполняется раньше вычитания") {
    Calculator calc;
    // 10 - 6/2 = 10 - 3 = 7, а не (10-6)/2 = 2
    CHECK(calc.calculate("10-6/2") == 7.0);
}

TEST_CASE("Несколько операций одного приоритета — слева направо") {
    Calculator calc;
    CHECK(calc.calculate("10-3-2") == 5.0);
    CHECK(calc.calculate("12/2/3") == doctest::Approx(2.0));
}

// ==================== Скобки ====================

TEST_CASE("Скобки меняют порядок вычисления") {
    Calculator calc;
    CHECK(calc.calculate("(2+2)*2") == 8.0);
}

TEST_CASE("Пример из задания: (8+10)*8") {
    Calculator calc;
    CHECK(calc.calculate("(8+10)*8") == 144.0);
}

TEST_CASE("Вложенные скобки") {
    Calculator calc;
    CHECK(calc.calculate("((2+3)*2)") == 10.0);
}

// ==================== Унарный минус ====================

TEST_CASE("Унарный минус перед числом") {
    Calculator calc;
    CHECK(calc.calculate("-5+10") == 5.0);
}

TEST_CASE("Унарный минус в скобках") {
    Calculator calc;
    CHECK(calc.calculate("(-3)*4") == -12.0);
}

// ==================== Дробные числа ====================

TEST_CASE("Дробные числа в выражении") {
    Calculator calc;
    CHECK(calc.calculate("1.5+1.5") == 3.0);
    CHECK(calc.calculate("0.1+0.2") == doctest::Approx(0.3));
}

// ==================== История ====================

TEST_CASE("История пуста при создании") {
    Calculator calc;
    CHECK(calc.getHistorySize() == 0);
    CHECK(calc.getHistory().empty());
}

TEST_CASE("После каждого вычисления история растёт") {
    Calculator calc;
    calc.calculate("2+2");
    CHECK(calc.getHistorySize() == 1);
    calc.calculate("3*3");
    CHECK(calc.getHistorySize() == 2);
}

TEST_CASE("История хранит правильные результаты") {
    Calculator calc;
    calc.calculate("5+5");
    calc.calculate("3*7");
    CHECK(calc.getHistory()[0].result == 10.0);
    CHECK(calc.getHistory()[1].result == 21.0);
}

TEST_CASE("Очистка истории работает") {
    Calculator calc;
    calc.calculate("2+2");
    calc.calculate("5-1");
    CHECK(calc.getHistorySize() == 2);
    calc.clearHistory();
    CHECK(calc.getHistorySize() == 0);
    CHECK(calc.getHistory().empty());
}

// ==================== Ошибки ====================

TEST_CASE("Деление на ноль бросает исключение") {
    Calculator calc;
    CHECK_THROWS_AS(calc.calculate("10/0"), std::invalid_argument);
    CHECK_THROWS_AS(calc.calculate("0/0"), std::invalid_argument);
}

TEST_CASE("После деления на ноль история не меняется") {
    Calculator calc;
    calc.calculate("2+2"); // одна запись

    try {
        calc.calculate("5/0");
    } catch (...) {}

    // В историю не должно записаться
    CHECK(calc.getHistorySize() == 1);
}

TEST_CASE("Пустое выражение бросает исключение") {
    Calculator calc;
    CHECK_THROWS_AS(calc.calculate(""), std::invalid_argument);
    CHECK_THROWS_AS(calc.calculate("   "), std::invalid_argument);
}

TEST_CASE("Некорректный символ бросает исключение") {
    Calculator calc;
    CHECK_THROWS_AS(calc.calculate("2@2"), std::invalid_argument);
    CHECK_THROWS_AS(calc.calculate("2+a"), std::invalid_argument);
}

TEST_CASE("Незакрытая скобка бросает исключение") {
    Calculator calc;
    CHECK_THROWS_AS(calc.calculate("(2+2"), std::invalid_argument);
}
