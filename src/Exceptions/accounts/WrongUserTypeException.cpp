//
// Created by Nuno Alves on 28/10/2020.
//

#include "WrongUserTypeException.h"

WrongUserTypeException::WrongUserTypeException(enum::userType type) : userType(type) {}

const char *WrongUserTypeException::what() const throw() {
    return "Wrong User Class sent to account constructor.";
}

/**
 * Outputs a detailed explanation to the user on why the exception was thrown
 *
 * @param os - Output stream
 * @param exception - The exception thrown
 * @return Output stream reference
 */
std::ostream &operator<<(std::ostream &os, const WrongUserTypeException &exception) {
    os << exception.userType << " is the wrong class.";
    return os;
}
