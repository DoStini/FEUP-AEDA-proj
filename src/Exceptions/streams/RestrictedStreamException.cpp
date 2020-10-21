//
// Created by andre on 10/21/2020.
//

#include "RestrictedStreamException.h"

#include <utility>

RestrictedStreamException::RestrictedStreamException(std::string streamName, std::string userName)
        : streamName(std::move(streamName)), userName(std::move(userName)) {}

std::ostream &operator<<(std::ostream &os, const RestrictedStreamException &exception) {
    os << "User " << exception.userName << " is not whitelisted in " << exception.streamName << ".";
    return os;
}

const char *RestrictedStreamException::what() const noexcept {
    return "User not whitelisted";
}
