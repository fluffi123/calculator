#include "calculator.h"
#include <sstream>
#include <cctype>
std::string calculator::Spaces(std::string input) {
    std::string newinput;
    int i = 0;
    while (i < input.size()) {
        char c = input[i];
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^' || c == '!') {
            newinput += ' ';
            newinput += c;
            newinput += ' ';
        }
        else {
            newinput += c;
        }
        i++;
    }
    return newinput;
}

std::vector<std::string> calculator::separate(std::string input) {
    input = Spaces(input);
    std::stringstream ss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

bool calculator::isNumber(const std::string& s) {
    if (s.empty()) return false;
    int i = 0;
    bool hasDigit = false;
    while (i < s.size()) {
        char c = s[i];
        if (isdigit(c)) {
            hasDigit = true;
        }
        else if (c == '.' && i != 0) {
        }
        else if (c == '-' && i == 0) {
        }
        else {
            return false;
        }
        i++;
    }
    return hasDigit;
}

bool calculator::isvalid(std::string tokens) {
    int i = 0;
    bool valid = true;
    while (i < tokens.size()) {
        if (isdigit(tokens[i]) || tokens[i] == '+' || tokens[i] == '-' || tokens[i] == '*' || tokens[i] == '/' || tokens[i] == '(' || tokens[i] == ')' || tokens[i] == '^' || tokens[i] == '.' || tokens[i] == '!' || tokens[i] == ' ') {
            i++;
        }
        else {
            valid = false;
            break;
        }
    }
    return valid;
}

int calculator::priority(std::string op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    if (op == "!") return 4;
    return 0;
}

double calculator::factorial(std::string a) {
    double answer = 1;
    int i = 1;
    while (std::stoi(a) >= i) {
        answer = i * answer;
        i++;
    }
    return answer;
}

double calculator::exponinantion(std::string a, std::string b) {
    double answer = 1;
    int i = 0;
    while (std::stod(b) > i) {
        answer = std::stod(a) * answer;
        i++;
    }
    return answer;
}

std::vector<std::string> calculator::toRPN(std::vector<std::string> tokens) {
    std::vector<std::string> output;
    std::vector<std::string> opStack;

    int i = 0;
    while (i < tokens.size()) {
        std::string token = tokens[i];

        if (isNumber(token)) {
            output.push_back(token);
        }
        else if (token == "(") {
            opStack.push_back(token);
        }
        else if (token == ")") {
            while (!opStack.empty() && opStack.back() != "(") {
                output.push_back(opStack.back());
                opStack.pop_back();
            }
            if (!opStack.empty()) {
                opStack.pop_back();
            }
        }
        else if (token == "!") {
            output.push_back(token);
        }
        else {
            while (!opStack.empty() && opStack.back() != "(" &&
                   (priority(opStack.back()) > priority(token) ||
                   (priority(opStack.back()) == priority(token) && token != "^"))) {
                output.push_back(opStack.back());
                opStack.pop_back();
            }
            opStack.push_back(token);
        }
        i++;
    }

    while (!opStack.empty()) {
        output.push_back(opStack.back());
        opStack.pop_back();
    }

    return output;
}

double calculator::evalRPN(std::vector<std::string> rpn) {
    std::vector<double> stack;

    int i = 0;
    while (i < rpn.size()) {
        std::string token = rpn[i];

        if (isNumber(token)) {
            stack.push_back(std::stod(token));
        }
        else if (token == "!") {
            double a = stack.back(); stack.pop_back();
            double result = factorial(std::to_string((int)a));
            stack.push_back(result);
        }
        else {
            double b = stack.back(); stack.pop_back();
            double a = stack.back(); stack.pop_back();
            double result = 0;
            if (token == "+") result = a + b;
            else if (token == "-") result = a - b;
            else if (token == "*") result = a * b;
            else if (token == "/") result = a / b;
            else if (token == "^") result = exponinantion(std::to_string(a), std::to_string(b));
            stack.push_back(result);
        }
        i++;
    }

    if (stack.empty()) return 0;
    return stack.back();
}
