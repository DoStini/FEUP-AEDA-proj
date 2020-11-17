//
// Created by Nuno Alves on 19/10/2020.
//

#include "BadDateFormat.h"

BadDateFormat::BadDateFormat(const std::string &date) : date(date) {}

const char *BadDateFormat::what() const throw() {
    return "Bad date format used when creating a Date object";
}

/**
 * Outputs a detailed explanation to the user on why the exception was thrown
 *
 * @param os - Output streamer
 * @param exception - The exception thrown
 * @return Output streamer reference
 */
std::ostream &operator<<(std::ostream &os, const BadDateFormat &exception) {
    os << exception.date << " is not a valid date format.";
    return os;
}
