//
// Created by andre on 10/21/2020.
//

#ifndef FEUP_AEDA_PROJ_UTILS_H
#define FEUP_AEDA_PROJ_UTILS_H

#define VIEWER_MIN_AGE 12
#define STREAMER_MIN_AGE 15
#define LINE_BREAK "\n#-----------------------------------#\n"
typedef long long int ID;


#include <iostream>
#include <limits>
#include<string>



/**
 * Function that prompts the user for input.
 * Checks if input is valid, allows only input without spaces and in the correct type.
 * Doesn't allow for the EOF character to be input, allowing for input to continue.
 *
 * @tparam T the type of data to be input
 * @param[out] input The variable where the input is stored.
 * @param[in] delimiter The last char must be at the end of the buffer
 *
 * @returns a boolean that indicates if a value was input successfully.
 */
template <typename T>
bool checkInput(T& input, char delimiter = '\n') {
    std::cin >> input;

    if (std::cin.eof()) {
        std::cin.clear();
        return false;
    }
    else if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return false;
    }
    else if (std::cin.peek() != delimiter) {
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return false;
    }

    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    return true;
}

template<typename T>
void print(T message, char end = '\n') {
    std::cout << message << end;
}

void print(char end = '\n');


enum language{
    PT_PT,
    PT_BR,
    ENG,
    SPA,
    FRE,
    GER,
    RUS,
    CHI,
    HINDI,
};

enum genre{
    gaming,
    technology,
    music,
    cooking,
    meetGreet,
};

void waitForKey();


#endif //FEUP_AEDA_PROJ_UTILS_H
