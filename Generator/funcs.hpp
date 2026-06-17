#include <iostream>
#include <random>
#include <vector>
#include <array>

inline
int random_num(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    int randomNumber = dist(mt);
    return randomNumber;
}

std::string get_upper(std::string str) {
    std::string new_string;
    for (char chr : str) {
        if (chr == ',' || chr == ' ') {
            continue;
        }

        if ((int)chr >= 96) {
            new_string += (char)((int)(chr - 32));
        } else {
            new_string += chr;
        }
    }


    return new_string;
}
