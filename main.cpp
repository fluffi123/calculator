#include "calculator.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    calculator calc;
    std::string input;
    std::string newinput = "";
    while (input != "exit") {
        std::cout << "Dictate \n" << newinput;
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
