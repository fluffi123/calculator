#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>

class calculator {
public:
    std::string Spaces(std::string input);
    std::vector<std::string> separate(std::string input);
    double exponinantion(std::string a, std::string b);
    bool isNumber(const std::string& s);
    bool isvalid(std::vector<std::string> tokens);
    double calcus(std::vector<std::string> tokens);
    std::vector<std::string> skobki(std::vector<std::string> tokens);
};

#endif
