//
// Created by Nuno Alves on 19/10/2020.
//

#include "InvalidDate.h"

const char *InvalidDate::what() const throw() {
    return "Date was not a valid date.";
}

/**
 * Outputs a detailed explanation to the user on why the exception was thrown
 *
 * @param os - Output stream
 * @param exception - The exception thrown
 * @return Output stream reference
 */
std::ostream &operator<<(std::ostream &os, const InvalidDate &exception) {
    os << "Date was not valid";
    return os;
}

