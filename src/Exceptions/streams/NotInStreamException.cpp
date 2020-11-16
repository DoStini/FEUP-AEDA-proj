//
// Created by andre on 10/18/2020.
//

#include "NotInStreamException.h"

NotInStreamException::NotInStreamException(std::string userName) : userName(userName) {}

const char *NotInStreamException::what() const noexcept {
    return "User not in streamer";
}

std::ostream &operator<<(std::ostream &os, const NotInStreamException &exception) {
    os << "The operation wasn't executed because " << exception.userName << " isn't in any active streamer.";
    return os;
}


