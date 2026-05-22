#include <iostream>
#define NOMINMAX
#include <windows.h>
#include <iomanip>
#include <limits>
#include "Calculator.h"

void printHistory(const Calculator& calc) {
    const auto& history = calc.getHistory();
    if (history.empty()) {
        std::cout << "История пуста.\n";
        return;
    }
    std::cout << "\n=== История вычислений ===\n";
    for (int i = 0; i < (int)history.size(); ++i) {
        std::cout << i + 1 << ". " << history[i].expression << "\n";
    }
    std::cout << "==========================\n\n";
}

void printMenu() {
    std::cout << "\nВыберите действие:\n"
              << "  1. Сложение        (+)\n"
              << "  2. Вычитание       (-)\n"
              << "  3. Умножение       (*)\n"
              << "  4. Деление         (/)\n"
              << "  5. Показать историю\n"
              << "  6. Очистить историю\n"
              << "  0. Выход\n"
              << "Ваш выбор: ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Calculator calc;
    int choice = -1;

    std::cout << "============================\n";
    std::cout << "   Калькулятор с историей   \n";
    std::cout << "============================\n";

    while (choice != 0) {
        printMenu();

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите число от 0 до 6.\n";
            continue;
        }

        if (choice >= 1 && choice <= 4) {
            double a, b;
            std::cout << "Введите первое число: ";
            std::cin >> a;
            std::cout << "Введите второе число: ";
            std::cin >> b;

            try {
                double result = 0;
                if      (choice == 1) result = calc.add(a, b);
                else if (choice == 2) result = calc.subtract(a, b);
                else if (choice == 3) result = calc.multiply(a, b);
                else if (choice == 4) result = calc.divide(a, b);

                std::cout << std::fixed << std::setprecision(6);
                std::cout << "Результат: " << result << "\n";
            } catch (const std::invalid_argument& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
            }
        } else if (choice == 5) {
            printHistory(calc);
        } else if (choice == 6) {
            calc.clearHistory();
            std::cout << "История очищена.\n";
        } else if (choice == 0) {
            std::cout << "До свидания!\n";
        } else {
            std::cout << "Неверный выбор. Введите число от 0 до 6.\n";
        }
    }

    return 0;
}
