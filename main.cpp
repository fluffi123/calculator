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
        std::cout << "Dictate. If you want to erase previous answer, write Wipe \n" << newinput;
        std::getline(std::cin, input);
        if (input == "Wipe"|| input == "wipe"||input == " Wipe" || input == " wipe") {
            newinput = "";
            std::cout << "Wiped successfully. Please write a new equation \n";
            std::getline(std::cin, input);
        }
            newinput = newinput + input;
        if (calc.isvalid(newinput) != true) {
            std::cout << "there was a mistake, please restart";
            break;
        }
        std::vector<std::string> tokens = calc.separate(newinput);
        std::vector<std::string> rpn = calc.toRPN(tokens);
        double answer = calc.evalRPN(rpn);
        std::cout << "answer is \n" << answer << "\n";
        newinput = std::to_string(answer);
    }
}
