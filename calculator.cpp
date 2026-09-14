#include "calculator.h"
#include <iostream>
#include <sstream>
#include <cctype>

std::string calculator::Spaces(std::string input) {
    std::string newinput;
    int i = 0;
    while (i < input.size()) {
        char c = input[i];
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^') {
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

double calculator::exponinantion(std::string a, std::string b) {
    double answer = 1;
    int i = 0;
    while (std::stoi(b) > i) {
        answer = std::stod(a) * answer;
        i++;
    }
    return answer;
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

bool calculator::isvalid(std::vector<std::string> tokens) {
    int i = 0;
    bool valid = true;
    while (i < tokens.size()) {
        if (isNumber(tokens[i]) || tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/" || tokens[i] == "(" || tokens[i] == ")" || tokens[i] == "^") {
            i++;
        }
        else {
            valid = false;
            break;
        }
    }
    return valid;
}

double calculator::calcus(std::vector<std::string> tokens) {
    int i = 0;
    while (i < tokens.size()) {
        if (tokens[i] == "^") {
            double result = exponinantion(tokens[i - 1], tokens[i + 1]);
            tokens[i] = std::to_string(result);
            tokens.erase(tokens.begin() + i + 1);
            tokens.erase(tokens.begin() + i - 1);
        }
        else {
            i++;
        }
    }
    i = 0;
    while (i < tokens.size()) {
        if (tokens[i] == "*") {
            double result = std::stod(tokens[i - 1]) * std::stod(tokens[i + 1]);
            tokens[i] = std::to_string(result);
            tokens.erase(tokens.begin() + i + 1);
            tokens.erase(tokens.begin() + i - 1);
        }
        else if (tokens[i] == "/") {
            double result = std::stod(tokens[i - 1]) / std::stod(tokens[i + 1]);
            tokens[i] = std::to_string(result);
            tokens.erase(tokens.begin() + i + 1);
            tokens.erase(tokens.begin() + i - 1);
        }
        else {
            i++;
        }
    }
    i = 0;
    while (i < tokens.size()) {
        if (tokens[i] == "+") {
            double result = std::stod(tokens[i - 1]) + std::stod(tokens[i + 1]);
            tokens[i] = std::to_string(result);
            tokens.erase(tokens.begin() + i + 1);
            tokens.erase(tokens.begin() + i - 1);
        }
        else if (tokens[i] == "-") {
            double result = std::stod(tokens[i - 1]) - std::stod(tokens[i + 1]);
            tokens[i] = std::to_string(result);
            tokens.erase(tokens.begin() + i + 1);
            tokens.erase(tokens.begin() + i - 1);
        }
        else {
            i++;
        }
    }
    double answer = std::stod(tokens[0]);
    return answer;
}

std::vector<std::string> calculator::skobki(std::vector<std::string> tokens) {
    while (true) {
        int openIdx = -1;
        int i = 0;
        while (i < tokens.size()) {
            if (tokens[i] == "(") {
                openIdx = i;
            }
            i++;
        }
        if (openIdx == -1) break;
        int closeIdx = -1;
        i = openIdx + 1;
        while (i < tokens.size()) {
            if (tokens[i] == ")") {
                closeIdx = i;
                break;
            }
            i++;
        }
        std::vector<std::string> inner;
        i = openIdx + 1;
        while (i < closeIdx) {
            inner.push_back(tokens[i]);
            i++;
        }
        double result = calcus(inner);
        std::vector<std::string> newTokens;
        i = 0;
        while (i < openIdx) {
            newTokens.push_back(tokens[i]);
            i++;
        }
        newTokens.push_back(std::to_string(result));
        i = closeIdx + 1;
        while (i < tokens.size()) {
            newTokens.push_back(tokens[i]);
            i++;
        }
        tokens = newTokens;
    }
    return tokens;
}
