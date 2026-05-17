#include "Calculator.h"
#include <sstream>
#include <iomanip>

// Вспомогательная функция: превращает число в строку без лишних нулей
static std::string numToStr(double n) {
    std::ostringstream ss;
    ss << std::setprecision(10) << n;
    return ss.str();
}

void Calculator::saveToHistory(const std::string& expression, double result) {
    history.push_back({expression, result});
}

double Calculator::add(double a, double b) {
    double result = a + b;
    saveToHistory(numToStr(a) + " + " + numToStr(b) + " = " + numToStr(result), result);
    return result;
}

double Calculator::subtract(double a, double b) {
    double result = a - b;
    saveToHistory(numToStr(a) + " - " + numToStr(b) + " = " + numToStr(result), result);
    return result;
}

double Calculator::multiply(double a, double b) {
    double result = a * b;
    saveToHistory(numToStr(a) + " * " + numToStr(b) + " = " + numToStr(result), result);
    return result;
}

double Calculator::divide(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("Деление на ноль недопустимо");
    }
    double result = a / b;
    saveToHistory(numToStr(a) + " / " + numToStr(b) + " = " + numToStr(result), result);
    return result;
}

const std::vector<HistoryEntry>& Calculator::getHistory() const {
    return history;
}

void Calculator::clearHistory() {
    history.clear();
}

int Calculator::getHistorySize() const {
    return static_cast<int>(history.size());
}
