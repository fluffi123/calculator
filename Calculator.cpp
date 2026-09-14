#include <iostream>
#include <sstream>
#include <vector>
class matrix {
public:

};
class calculator {
public:

    std::string Spaces(std::string input) {
        std::string newinput;
        int i = 0;
        while (i < input.size()) {
            char c = input[i];
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'|| c == '^'||c =='!') {
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

    std::vector<std::string> separate(std::string input) {
        input = Spaces(input);
        std::stringstream ss(input);
        std::vector<std::string> tokens;
        std::string token;
        while (ss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }

    double factorial(std::string a) {
        double answer = 1;
        int i = 1;
        while (std::stoi(a) >= i) {
            answer = i * answer;
            i++;
        }
        return answer;
    }

    double exponinantion(std::string a, std::string b) {
        double answer = 1;
        int i = 0;
        while (std::stod(b) > i) {
            answer = std::stod(a) * answer;
            i++;
        }
        return answer;
    }

    void page(std::string input) {
        std::cin >> input;
        while (input != "exit") {
            if (input == "help") {
                std::cout << "here is possible actions \n 1.Print 'exit' to end code \n 2. Print 'help' for list of actions \n 3. Print 'matrix' for solving equations with them";
            }
            else if (input == "matrix") {
                break;
            }
        }
    }

    bool isvalid(std::string tokens) {
        int i = 0;
        bool valid = true;
        while (i < tokens.size()) {
            if (isdigit(tokens[i])|| tokens[i] == '+'  || tokens[i] == '-' || tokens[i] == '*' || tokens[i] == '/' || tokens[i] == '(' || tokens[i] == ')' || tokens[i] == '^'||tokens[i]=='.'||tokens[i]=='!') {
                i++;
            }
            else {
                valid = false;
                break;
            }
        }
        return valid;
    }

    double calcus(std::vector<std::string> tokens) {
        int i = 0;
        while (i < tokens.size()) {
            if (tokens[i] == "^") {
                double result = exponinantion(tokens[i - 1],tokens[i+1]);
                tokens[i] = std::to_string(result);
                tokens.erase(tokens.begin() + i + 1);
                tokens.erase(tokens.begin() + i - 1);
            }
            else if (tokens[i] == "!"){
                double result = factorial(tokens[i - 1]);
                tokens[i] = std::to_string(result);
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

    std::vector<std::string> skobki(std::vector<std::string> tokens) {
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
            newTokens.push_back(std::to_string((int)result));
            i = closeIdx + 1;
            while (i < tokens.size()) {
                newTokens.push_back(tokens[i]);
                i++;
            }
            tokens = newTokens;
        }
        return tokens;
    }
};

int main()
{
    calculator calc;
    std::string input;
    std::string newinput = "";
    while (input != "exit") {
        std::cout << "Dictate \n"<< newinput;
        std::getline(std::cin, input);
        newinput = newinput + input;
        if (calc.isvalid(newinput) != true) {
            std::cout << "there was a mistake, please restart";
            break;
        }
        std::vector<std::string> tokens = calc.separate(newinput);
        tokens = calc.skobki(tokens);
        double answer = calc.calcus(tokens);
        std::cout << "answer is \n" << answer << "\n";
        newinput = std::to_string(answer);
    }
}
