//
// Created by andre on 10/17/2020.
//

#include "RestrictedAgeException.h"

#include <utility>

RestrictedAgeException::RestrictedAgeException(std::string name, int age, int minAge) : name(std::move(name)), age(age),
                                                                                               minAge(minAge) {}

const char *RestrictedAgeException::what() const throw() {
    return "Minimum age failed";
}

/**
 * Outputs a detailed explanation to the user on why the exception was thrown
 *
 * @param os - Output streamer
 * @param exception - The exception thrown
 * @return Output streamer reference
 */
std::ostream &operator<<(std::ostream &os, const RestrictedAgeException &exception) {
    os << exception.name << ", " << exception.age << " years old, is younger than the minimum age required "
       << exception.minAge << " years old.";
    return os;
}
