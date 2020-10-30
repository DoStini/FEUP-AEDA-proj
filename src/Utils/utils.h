//
// Created by andre on 10/21/2020.
//

#ifndef FEUP_AEDA_PROJ_UTILS_H
#define FEUP_AEDA_PROJ_UTILS_H

#define KEY_ESC 27
#define VIEWER_MIN_AGE 12
#define STREAMER_MIN_AGE 15
#define LINE_BREAK "\n#-----------------------------------#\n"
typedef unsigned long long int ID;


#include <iostream>
#include <limits>
#include<string>
#include <algorithm>



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
    PT_PT = 0,
    PT_BR,
    ENG,
    SPA,
    FRE,
    GER,
    RUS,
    CHI,
    HINDI,
    LASTL
};

enum genre{
    gaming = 0,
    technology,
    music,
    cooking,
    meetGreet,
    LASTG
};

void waitForKey();

void getString(std::string &string);

std::string stringToLower(std::string string);

/**
 * Function that prompts the user for the input of a single char.
 * Reads only the first char input to the buffer, all else is deleted from the buffer.
 * Allows the EOF character.
 *
 * @param[out] input The variable where the input is stored.
 */
void getChar(char& input);


#endif //FEUP_AEDA_PROJ_UTILS_H
