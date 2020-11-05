//
// Created by Nuno Alves on 05/11/2020.
//

#include "MaxViewersReach.h"

std::ostream &operator<<(std::ostream &os, const MaxViewersReach &exception) {
    return os;
}

const char *MaxViewersReach::what() const noexcept {
    return exception::what();
}
