//
// Created by adbp on 24/10/2020.
//

#include "NotPrivateStreamException.h"


NotPrivateStreamException::NotPrivateStreamException(std::string streamName)
        : streamName(std::move(streamName)) {}

std::ostream &operator<<(std::ostream &os, const NotPrivateStreamException &exception) {
    os << "Stream " << exception.streamName << " is not a private stream.";
    return os;
}

const char *NotPrivateStreamException::what() const noexcept {
    return "Stream is not private";
}