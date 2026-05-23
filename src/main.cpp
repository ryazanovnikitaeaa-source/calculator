#include <iostream>
#include <string>
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif
#include "Calculator.h"

void printHistory(const Calculator& calc) {
    const auto& history = calc.getHistory();
    if (history.empty()) {
        std::cout << "История пуста.\n";
        return;
    }
    std::cout << "\n=== История вычислений ===\n";
    for (int i = 0; i < (int)history.size(); i++) {
        std::cout << i + 1 << ". " << history[i].expression << "\n";
    }
    std::cout << "==========================\n\n";
}

void printMenu() {
    std::cout << "\nВыберите действие:\n"
              << "  1. Вычислить выражение\n"
              << "  2. Показать историю\n"
              << "  3. Очистить историю\n"
              << "  0. Выход\n"
              << "Ваш выбор: ";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001); // CP_UTF8
#endif

    Calculator calc;
    int choice = -1;

    std::cout << "============================\n";
    std::cout << "   Калькулятор с историей   \n";
    std::cout << "============================\n";
    std::cout << "Поддерживаются: + - * / и скобки\n";
    std::cout << "Примеры: 2+2*2    (8+10)*8    100/4-5\n";

    while (choice != 0) {
        printMenu();

        std::string line;
        std::getline(std::cin, line);

        // Проверяем, что введено корректное число
        bool valid = !line.empty();
        for (int i = 0; i < (int)line.size(); i++) {
            if (line[i] < '0' || line[i] > '9') {
                valid = false;
                break;
            }
        }

        if (!valid) {
            std::cout << "Ошибка: введите число от 0 до 3.\n";
            continue;
        }

        choice = std::stoi(line);

        if (choice == 1) {
            std::cout << "Введите выражение: ";
            std::string expression;
            std::getline(std::cin, expression);

            try {
                double result = calc.calculate(expression);
                std::cout << "Результат: " << result << "\n";
            } catch (const std::invalid_argument& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
            }

        } else if (choice == 2) {
            printHistory(calc);

        } else if (choice == 3) {
            calc.clearHistory();
            std::cout << "История очищена.\n";

        } else if (choice == 0) {
            std::cout << "До свидания!\n";

        } else {
            std::cout << "Неверный выбор. Введите от 0 до 3.\n";
        }
    }

    return 0;
}
