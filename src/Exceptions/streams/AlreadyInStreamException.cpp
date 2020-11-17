//
// Created by andre on 10/18/2020.
//

#include "AlreadyInStreamException.h"

#include <utility>


const char *AlreadyInStreamException::what() const noexcept {
    return "User already in streamer";
}

std::ostream &operator<<(std::ostream &os, const AlreadyInStreamException &exception) {
    os << "The operation " << exception.user << " requested wasn't executed because the user is already "
    << (exception.isViewer ? "watching " : "streaming ") << exception.currStream << ".";
    return os;
}

AlreadyInStreamException::AlreadyInStreamException(std::string user,  ID streamWatching,bool viewer) : user(std::move(user)), currStream(std::move(streamWatching)), isViewer(viewer) {}


