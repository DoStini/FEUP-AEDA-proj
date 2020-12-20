//
// Created by andre on 10/17/2020.
//

#include "NoSuchOrderException.h"

#include <utility>

NoSuchOrderException::NoSuchOrderException(const std::string& name) : userName(name)  {}

const char *NoSuchOrderException::what() const throw() {
    return "No orders";
}

/**
 * Outputs a detailed explanation to the user on why the exception was thrown
 * @return Output stream reference
 */
std::ostream &operator<<(std::ostream &os, const NoSuchOrderException &exception) {
    os << "No such order from username " << exception.userName << "!";
    return os;
}
