#include "expression_evaluator.h"
#include <sstream>
#include <stdexcept>
#include <stack>
#include <cctype>
#include <cmath>
#include <iostream>
#include <unordered_map>

namespace Calculator {

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isNumber(const std::string& token) {
    char* end = nullptr;
    strtod(token.c_str(), &end);
    return end != nullptr && *end == '\0';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::invalid_argument("Division by zero");
            return a / b;
        default: throw std::invalid_argument("Invalid operator");
    }
}

std::string infixToPostfix(const std::string& infix) {
    std::stack<char> operators;
    std::ostringstream postfix;
    size_t i = 0;

    while (i < infix.size()) {
        if (std::isspace(infix[i])) {
            ++i;
            continue;
        }

        if (std::isdigit(infix[i]) || infix[i] == '.') {
            while (i < infix.size() && (std::isdigit(infix[i]) || infix[i] == '.')) {
                postfix << infix[i];
                ++i;
            }
            postfix << ' ';
        } else if (infix[i] == '(') {
            operators.push(infix[i]);
            ++i;
        } else if (infix[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix << operators.top() << ' ';
                operators.pop();
            }
            if (operators.empty() || operators.top() != '(') {
                throw std::invalid_argument("Mismatched parentheses");
            }
            operators.pop();
            ++i;
        } else if (isOperator(infix[i])) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(infix[i])) {
                postfix << operators.top() << ' ';
                operators.pop();
            }
            operators.push(infix[i]);
            ++i;
        } else {
            throw std::invalid_argument("Invalid character in expression");
        }
    }

    while (!operators.empty()) {
        if (operators.top() == '(') {
            throw std::invalid_argument("Mismatched parentheses");
        }
        postfix << operators.top() << ' ';
        operators.pop();
    }

    return postfix.str();
}

} // namespace Calculator

double evaluateExpression(const std::string& expression) {
    std::string postfix = Calculator::infixToPostfix(expression);
    std::stack<double> values;
    std::istringstream tokens(postfix);
    std::string token;

    while (tokens >> token) {
        if (Calculator::isNumber(token)) {
            values.push(std::stod(token));
        } else if (token.size() == 1 && Calculator::isOperator(token[0])) {
            if (values.size() < 2) {
                throw std::invalid_argument("Invalid expression");
            }
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            values.push(Calculator::applyOperation(a, b, token[0]));
        } else {
            throw std::invalid_argument("Invalid token in expression");
        }
    }

    if (values.size() != 1) {
        throw std::invalid_argument("Invalid expression");
    }

    return values.top();
}
