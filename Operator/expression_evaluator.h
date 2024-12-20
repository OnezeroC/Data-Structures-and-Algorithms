#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <string>
#include <stdexcept>
#include <stack>
#include <cctype>
#include <cmath>

// Function to evaluate an arithmetic expression
double evaluateExpression(const std::string& expression);

// Helper functions for internal usage
namespace Calculator {
    // Check if a character is an operator
    bool isOperator(char c);

    // Check if a string is a valid number
    bool isNumber(const std::string& token);

    // Get precedence of an operator
    int precedence(char op);

    // Perform arithmetic operation
    double applyOperation(double a, double b, char op);

    // Convert infix expression to postfix
    std::string infixToPostfix(const std::string& infix);
}

#endif
