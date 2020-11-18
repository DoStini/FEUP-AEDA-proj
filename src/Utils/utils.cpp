//
// Created by Nuno Alves on 28/10/2020.
//

#include "utils.h"

void print(char end) {
    std::cout << end;
}

std::string stringToLower(std::string string) {
    std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c) {return std::tolower(c);});

    return string;
}

void getString(std::string &string) {
    std::getline(std::cin, string);
}

void getTruncatedString(std::string &string) {
    std::getline(std::cin, string);
    std::stringstream  ss;

    ss << string;

    std::getline(ss, string, ' ');
}


void getChar(char &input) {
    input = getchar();
    if(input != '\n' && input != EOF) std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

void waitForKey() {
    char buffer;

    std::cout << "Press ENTER/RETURN to continue..." << std::endl;
    getChar(buffer);
}



