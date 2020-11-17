//
// Created by adbp on 24/10/2020.
//

#include "NotPrivateStreamException.h"


NotPrivateStreamException::NotPrivateStreamException(unsigned long long int streamId)
        : streamId(streamId) {}

std::ostream &operator<<(std::ostream &os, const NotPrivateStreamException &exception) {
    os << "Stream " << exception.streamId << " is not a private streamer.";
    return os;
}

const char *NotPrivateStreamException::what() const noexcept {
    return "Stream is not private";
}