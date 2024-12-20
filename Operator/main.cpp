#include <iostream>
#include <string>
#include "expression_evaluator.h"

int main() {
    std::string input;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, input);

    try {
        double result = evaluateExpression(input);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "ILLEGAL" << std::endl;
    }

    return 0;
}
