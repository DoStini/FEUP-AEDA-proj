//
// Created by andre on 10/21/2020.
//

#ifndef FEUP_AEDA_PROJ_UTILS_H
#define FEUP_AEDA_PROJ_UTILS_H

#define VIEWER_MIN_AGE 12
#define STREAMER_MIN_AGE 15

#define NULL_STREAM 0

#define MAX_VIEWERS 10
#define LINE_BREAK "\n#-----------------------------------#\n"


#include <iostream>
#include <limits>
#include<string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <functional>

/// Waits for input to continue;
void waitForKey();

/**
 * Gets a string with spaces.
 *
 * @param string variable passed in reference where the string will be output.
 */
void getString(std::string &string);

/**
 * Gets a string and truncates after space.
 *
 * @param string variable passed in reference where the string will be output.
 */
void getTruncatedString(std::string &string);

/**
 * Turns a string to lowercase
 *
 * @param string
 * @return a copy of the string in lowercase
 */
std::string stringToLower(std::string string);

/**
 * Function that prompts the user for the input of a single char.
 * Reads only the first char input to the buffer, all else is deleted from the buffer.
 * Allows the EOF character.
 *
 * @param[out] input The variable where the input is stored.
 */
void getChar(char& input);

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

/**
 * Prints a vector in pages.
 *
 * @tparam T the type of data in the vector
 * @param[in] list The vector to be printed
 * @param printFunction A std::function that returns a string containing information of the data to be listed
 */
template<typename T>
void printPagedList(std::vector<T> list, std::function<std::string(T)> printFunction) {
    char action;
    unsigned order = 1, page = 1;
    std::stringstream ss;
    auto it = list.begin();

    while(action != 'S' && it != list.end()) {
        ss.str("");
        ss << "Page " << page << ": ";
        print(ss.str());
        print();

        for(int _ = 0; _ < 10 && it != list.end(); order++, it++, _++) {
            ss.str("");
            ss << order << ". " << printFunction((*it));
            print(ss.str());
        }

        if(it == list.end()) {
            print();
            print("End of list.");
            return;
        }

        print();
        print("Press ENTER to show more items, write 'S' to leave.");

        getChar(action);
        action = toupper(action);

        page++;
    }
}

enum streamType{
    publicType = 1,
    privateType
};

enum streamFileType{
    publicFile = 1,
    privateFile,
    finishedFile
};

enum streamState{
    livestream = 1,
    finished
};

enum userType{
    viewer = 1,
    streamer,
    admin,
};

enum language{
    PT_PT = 1,
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
    gaming = 1,
    technology,
    music,
    cooking,
    meetGreet,
    LASTG
};

typedef unsigned long long int ID;


#endif //FEUP_AEDA_PROJ_UTILS_H
