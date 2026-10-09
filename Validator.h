#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <iostream>
#include <string>
#include <limits>

class Validator {
public:
    static int getInteger(int minVal, int maxVal) {
        int val;
        while (true) {
            std::cin >> val;
            if (!std::cin.fail() && val >= minVal && val <= maxVal) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return val;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a number (" << minVal << "-" << maxVal << "): ";
        }
    }

    static void getString(char* dest, size_t maxLen) {
        std::string input;
        while (true) {
            std::getline(std::cin, input);
            if (!input.empty() && input.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
                std::strncpy(dest, input.c_str(), maxLen - 1);
                dest[maxLen - 1] = '\0';
                return;
            }
            std::cout << "Field cannot be empty. Try again: ";
        }
    }
};

#endif