#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Определяем приоритеты операций
int getPriority(char op) {
    // Возвращает приоритет операции op
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

// Преобразует инфиксную запись в постфиксную
string infixToPostfix(string infix) {
    stack<char> s; // Стек для хранения операторов
    string postfix;
    for (char c : infix) {
        // Перебираем символы в infix
        if (isalnum(c)) {
            // Если символ является  цифрой
            postfix += c; // Добавляем его в postfix
        }
        else if (c == '(') {
            // Если символ является открывающей скобкой
            s.push(c); // Добавляем его в стек
        }
        else if (c == ')') {
            // Если символ является закрывающей скобкой
            while (!s.empty() && s.top() != '(') {
                // Пока в стеке не встретится открывающая скобка
                postfix += s.top(); // Добавляем операторы из стека в postfix
                s.pop(); // Удаляем операторы из стека
            }
            if (!s.empty()) {
                // Удаляем открывающую скобку из стека
                s.pop();
            }
        }
        else {
            // Если символ является оператором
            while (!s.empty() && getPriority(s.top()) >= getPriority(c)) {
                // Пока в стеке есть операторы с приоритетом >= c
                postfix += s.top(); // Добавляем операторы из стека в postfix
                s.pop(); // Удаляем операторы из стека
            }
            s.push(c); // Добавляем оператор c в стек
        }
    }
    while (!s.empty()) {
        // Добавляем оставшиеся операторы из стека в postfix
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

// Вычисляет постфиксное выражение
int evaluatePostfix(string postfix) {

    stack<int> s; // Стек для хранения операндов
    for (char c : postfix) {
        // Перебираем символы в postfix
        if (isdigit(c)) {
            // Если символ является цифрой
            s.push(c - '0'); // Добавляем его в стек (преобразуя в int)
        }
        else {
            // Если символ является оператором
            int operand2 = s.top(); // Извлекаем второй операнд из стека
            s.pop();
            int operand1 = s.top(); // Извлекаем первый операнд из стека
            s.pop();
            int result; // Переменная для хранения результата операции
            switch (c) {
                // Выполняем операцию в зависимости от символа
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            }
            s.push(result); // Добавляем результат операции в стек
        }
    }
    return s.top(); // Возвращаем результат вычисления
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Ввод выражения
    string infix;
    cout << "Введите выражение в инфиксной записи: ";
    cin >> infix;

    // Преобразование в постфиксную запись
    string postfix = infixToPostfix(infix);
    cout << "Постфиксная запись: " << postfix << endl;

    int result = evaluatePostfix(postfix);
    cout << "Результат: " << result << endl;

    return 0;
}