//
// Created by Nuno Alves on 06/11/2020.
//

#include "NotInWhiteListException.h"

std::ostream &operator<<(std::ostream &os, const NotInWhiteListException &exception) {
    return os;
}

const char *NotInWhiteListException::what() const noexcept {
    return exception::what();
}
