/**
 * Created by Stephen A. Adubi on Sept. 28, 2026.
 * This program evaluates postfix expressions using the stack data structure
 */

#include<stack>
#include <iostream>
#include <sstream>
#include <string>

double evaluate(const std::string& opr1, const std::string& opr2, const std::string& op) {
    try {
        double first = std::stod(opr1);
        double second = std::stod(opr2);
        if (op == "+")
            return first + second;
        if (op == "-")
            return first - second;
        if (op == "*")
            return first * second;
        if (op == "/")
            return first / second;
        std::cerr << "Unrecognized operator: " << op << "\n";
        exit(1);
    }
    catch (std::exception& e) {
        std::cout << "An error occurred!";
        std::cerr << e.what() << '\n';
        exit(1);
    }
}

bool is_operator(const std::string& opr) {
    if (opr == "+" || opr == "-" || opr == "*" || opr == "/")
        return true;
    return false;
}

int main() {
    std::string str;
    std::string input;
    std::stack<std::string> postfix_stack;
    std::cout << "Enter an expression (press return at the end of the input): ";
    std::getline(std::cin, input);
    std::istringstream iss(input);

    while (iss >> str) {
        if (!is_operator(str))
            postfix_stack.push(str);
        else { // if the token is an operator
            if (postfix_stack.size() >= 2) {
                std::string right_opr = postfix_stack.top();
                postfix_stack.pop();
                std::string left_opr = postfix_stack.top();
                postfix_stack.pop();
                double result = evaluate(left_opr, right_opr, str);
                postfix_stack.push(std::to_string(result));
            }
            else {
                std::cout << "An invalid expression is detected before the end of input parsing";
                exit(1);
            }
        }
    }

    if (postfix_stack.size() == 1)
        std::cout << "Postfix expression result: " << postfix_stack.top();
    else
        std::cout << "No result from the Postfix expression, likely due to invalid input";

    return 0;
}
