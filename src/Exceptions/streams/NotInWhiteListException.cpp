//
// Created by andremoreira9 on 05/11/20.
//

#include "NotInWhiteListException.h"

#include <utility>

NotInWhiteListException::NotInWhiteListException(std::string user, ID streamWhilisted)
        : user(std::move(user)), streamWhilisted(streamWhilisted) {}

std::ostream &operator<<(std::ostream &os, const NotInWhiteListException &exception) {
    os << "The operation " << exception.user << " requested wasn't executed because he isn't in the whitelist of " << exception.streamWhilisted << ".";
    return os;
}

const char *NotInWhiteListException::what() const noexcept {
    return "User not in streamer whitelist";
}
