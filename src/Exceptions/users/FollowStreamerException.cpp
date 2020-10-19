//
// Created by andre on 10/18/2020.
//

#include "FollowStreamerException.h"

FollowStreamerException::FollowStreamerException(bool following, const std::string &streamer, const std::string &user)
        : following(following), streamer(streamer), user(user) {}


const char *FollowStreamerException::what() const noexcept {
    return "Following streamer error";
}

std::ostream &operator<<(std::ostream &os, const FollowStreamerException &exception) {
    os << "The operation wasn't executed because " << exception.user << (exception.following ? " was already" : " wasn't") << " following " << exception.streamer << ".";
    return os;
}

