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
    // Вычислить строку-выражение
    // Бросает std::invalid_argument если выражение некорректное
    double calculate(const std::string& expression);

    // История вычислений
    const std::vector<HistoryEntry>& getHistory() const;
    void clearHistory();
    int getHistorySize() const;

private:
    std::vector<HistoryEntry> history;
};
