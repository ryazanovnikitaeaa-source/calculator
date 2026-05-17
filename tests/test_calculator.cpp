// Подключаем doctest — одна строка, библиотека встроена в заголовок
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/Calculator.h"

// ==================== Тесты сложения ====================

TEST_CASE("Сложение положительных чисел") {
    Calculator calc;
    CHECK(calc.add(2, 3) == 5);
    CHECK(calc.add(0, 0) == 0);
    CHECK(calc.add(100, 200) == 300);
}

TEST_CASE("Сложение отрицательных чисел") {
    Calculator calc;
    CHECK(calc.add(-5, -3) == -8);
    CHECK(calc.add(-10, 10) == 0);
}

// ==================== Тесты вычитания ====================

TEST_CASE("Вычитание чисел") {
    Calculator calc;
    CHECK(calc.subtract(10, 3) == 7);
    CHECK(calc.subtract(0, 5) == -5);
    CHECK(calc.subtract(-4, -4) == 0);
}

// ==================== Тесты умножения ====================

TEST_CASE("Умножение чисел") {
    Calculator calc;
    CHECK(calc.multiply(3, 4) == 12);
    CHECK(calc.multiply(-2, 5) == -10);
    CHECK(calc.multiply(0, 999) == 0);
    CHECK(calc.multiply(-3, -3) == 9);
}

// ==================== Тесты деления ====================

TEST_CASE("Деление чисел") {
    Calculator calc;
    CHECK(calc.divide(10, 2) == 5);
    CHECK(calc.divide(7, 2) == doctest::Approx(3.5));
    CHECK(calc.divide(-9, 3) == -3);
}

TEST_CASE("Деление на ноль бросает исключение") {
    Calculator calc;
    // Проверяем, что при делении на 0 выбрасывается invalid_argument
    CHECK_THROWS_AS(calc.divide(5, 0), std::invalid_argument);
    CHECK_THROWS_AS(calc.divide(0, 0), std::invalid_argument);
}

// ==================== Тесты истории ====================

TEST_CASE("История пуста при создании калькулятора") {
    Calculator calc;
    CHECK(calc.getHistorySize() == 0);
    CHECK(calc.getHistory().empty());
}

TEST_CASE("После операции история увеличивается") {
    Calculator calc;
    calc.add(1, 2);
    CHECK(calc.getHistorySize() == 1);

    calc.subtract(5, 3);
    CHECK(calc.getHistorySize() == 2);

    calc.multiply(4, 4);
    CHECK(calc.getHistorySize() == 3);
}

TEST_CASE("История содержит правильные результаты") {
    Calculator calc;
    calc.add(10, 5);
    calc.multiply(3, 7);

    CHECK(calc.getHistory()[0].result == 15);
    CHECK(calc.getHistory()[1].result == 21);
}

TEST_CASE("Очистка истории работает корректно") {
    Calculator calc;
    calc.add(1, 1);
    calc.subtract(5, 2);
    CHECK(calc.getHistorySize() == 2);

    calc.clearHistory();
    CHECK(calc.getHistorySize() == 0);
    CHECK(calc.getHistory().empty());
}

TEST_CASE("После деления на ноль история не изменяется") {
    Calculator calc;
    calc.add(1, 1); // одна запись

    try {
        calc.divide(5, 0); // должна бросить исключение и НЕ писать в историю
    } catch (...) {}

    // История должна остаться с одной записью
    CHECK(calc.getHistorySize() == 1);
}

TEST_CASE("История содержит правильные выражения в виде строк") {
    Calculator calc;
    calc.add(2, 3);
    // Выражение должно содержать все ключевые части
    const std::string& expr = calc.getHistory()[0].expression;
    CHECK(expr.find("2") != std::string::npos);
    CHECK(expr.find("3") != std::string::npos);
    CHECK(expr.find("+") != std::string::npos);
}
