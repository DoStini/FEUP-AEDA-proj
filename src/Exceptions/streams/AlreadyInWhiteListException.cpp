//
// Created by adbp on 02/11/2020.
//

#include "AlreadyInWhiteListException.h"

const char *AlreadyInWhiteListException::what() const noexcept {
    return "User already in streamer whitelist";
}

std::ostream &operator<<(std::ostream &os, const AlreadyInWhiteListException &exception) {
    os << "The operation " << exception.user << " requested wasn't executed because he is already in the whitelist of " << exception.streamWhilisted << ".";
    return os;
}

AlreadyInWhiteListException::AlreadyInWhiteListException(std::string user,  ID streamWhilisted) :
        user(std::move(user)),  streamWhilisted(std::move(streamWhilisted)){}

