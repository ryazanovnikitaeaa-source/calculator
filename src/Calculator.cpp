#include "Calculator.h"

// Парсер выражений методом рекурсивного спуска.
//
// Идея: делим грамматику на уровни приоритета.
// Нижний уровень (parseExpr) обрабатывает + и -,
// средний (parseTerm) — * и /,
// верхний (parseFactor) — числа и скобки.


// Текущая позиция в строке — храним как отдельную переменную,
// передаём по ссылке в каждую функцию
static double parseExpr(const std::string& s, int& pos);
static double parseTerm(const std::string& s, int& pos);
static double parseFactor(const std::string& s, int& pos);

// Пропустить пробелы
static void skipSpaces(const std::string& s, int& pos) {
    while (pos < (int)s.size() && s[pos] == ' ') {
        pos++;
    }
}

// Прочитать число
static double parseNumber(const std::string& s, int& pos) {
    skipSpaces(s, pos);

    if (pos >= (int)s.size()) {
        throw std::invalid_argument("Ожидалось число, но строка закончилась");
    }

    int start = pos;

    while (pos < (int)s.size() && (isdigit(s[pos]) || s[pos] == '.')) {
        pos++;
    }

    if (pos == start) {
        throw std::invalid_argument(std::string("Неожиданный символ: ") + s[pos]);
    }

    // Ручное преобразование строки в число
    double integer = 0;
    double decimal = 0;
    double decimalStep = 0.1;
    bool afterDot = false;
    bool doubleDot = false;

    for (int i = start; i < pos; i++) {
        if (s[i] == '.') {
            if (afterDot) {
                doubleDot = true;
                break;
            }
            afterDot = true;
        } else {
            int digit = s[i] - '0';
            if (!afterDot) {
                integer = integer * 10 + digit;
            } else {
                decimal += digit * decimalStep;
                decimalStep *= 0.1;
            }
        }
    }

    if (doubleDot) {
        throw std::invalid_argument("Некорректное число: две точки");
    }

    return integer + decimal;
}

// Уровень 3 — числа, скобки, унарный минус
static double parseFactor(const std::string& s, int& pos) {
    skipSpaces(s, pos);

    // Унарный минус: -5 или -(2+3)
    if (pos < (int)s.size() && s[pos] == '-') {
        pos++;
        return -parseFactor(s, pos);
    }

    // Унарный плюс
    if (pos < (int)s.size() && s[pos] == '+') {
        pos++;
        return parseFactor(s, pos);
    }

    // Скобки: ( выражение )
    if (pos < (int)s.size() && s[pos] == '(') {
        pos++; // съедаем '('
        double value = parseExpr(s, pos);
        skipSpaces(s, pos);
        if (pos >= (int)s.size() || s[pos] != ')') {
            throw std::invalid_argument("Ожидалась закрывающая скобка ')'");
        }
        pos++; // съедаем ')'
        return value;
    }

    // Просто число
    return parseNumber(s, pos);
}

// Уровень 2 — умножение и деление
static double parseTerm(const std::string& s, int& pos) {
    double left = parseFactor(s, pos);

    while (true) {
        skipSpaces(s, pos);
        if (pos >= (int)s.size()) break;

        char op = s[pos];
        if (op != '*' && op != '/') break;

        pos++; // съедаем оператор
        double right = parseFactor(s, pos);

        if (op == '*') {
            left = left * right;
        } else {
            if (right == 0.0) {
                throw std::invalid_argument("Деление на ноль недопустимо");
            }
            left = left / right;
        }
    }

    return left;
}

// Уровень 1 — сложение и вычитание (самый низкий приоритет)
static double parseExpr(const std::string& s, int& pos) {
    double left = parseTerm(s, pos);

    while (true) {
        skipSpaces(s, pos);
        if (pos >= (int)s.size()) break;

        char op = s[pos];
        if (op != '+' && op != '-') break;

        pos++; // съедаем оператор
        double right = parseTerm(s, pos);

        if (op == '+') {
            left = left + right;
        } else {
            left = left - right;
        }
    }

    return left;
}


// Методы класса Calculator


double Calculator::calculate(const std::string& expression) {
    // Убрать пробелы по краям
    int start = 0;
    int end = (int)expression.size() - 1;
    while (start <= end && expression[start] == ' ') start++;
    while (end >= start && expression[end] == ' ') end--;

    if (start > end) {
        throw std::invalid_argument("Пустое выражение");
    }

    std::string trimmed = expression.substr(start, end - start + 1);

    int pos = 0;
    double result = parseExpr(trimmed, pos);

    // Проверяем, что дошли до конца строки
    skipSpaces(trimmed, pos);
    if (pos < (int)trimmed.size()) {
        throw std::invalid_argument(
            std::string("Неожиданный символ: ") + trimmed[pos]
        );
    }

    history.push_back({trimmed + " = " + std::to_string(result), result});
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
