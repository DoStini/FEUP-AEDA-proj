//
// Created by Nuno Alves on 05/11/2020.
//

#include "AlreadyInWhiteListException.h"

std::ostream &operator<<(std::ostream &os, const AlreadyInWhiteListException &exception) {
    os << "test";
    return os;
}

const char *AlreadyInWhiteListException::what() const noexcept {
    return exception::what();
}
