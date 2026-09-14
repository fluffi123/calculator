#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>

class calculator {
public:
    std::string Spaces(std::string input);
    std::vector<std::string> separate(std::string input);
    double factorial(std::string a);
    double exponinantion(std::string a, std::string b);
    bool isvalid(std::string tokens);
    double calcus(std::vector<std::string> tokens);
    std::vector<std::string> skobki(std::vector<std::string> tokens);
};

#endif
