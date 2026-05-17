#pragma once

#include <string>
#include <vector>
#include <stdexcept>

// Одна запись в истории: выражение и результат
struct HistoryEntry {
    std::string expression;
    double result;
};

// Основной класс калькулятора
class Calculator {
public:
    // Арифметические операции
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b); // бросает std::invalid_argument при делении на 0

    // История вычислений
    const std::vector<HistoryEntry>& getHistory() const;
    void clearHistory();
    int getHistorySize() const;

private:
    std::vector<HistoryEntry> history;

    // Сохраняет операцию в историю
    void saveToHistory(const std::string& expression, double result);
};
