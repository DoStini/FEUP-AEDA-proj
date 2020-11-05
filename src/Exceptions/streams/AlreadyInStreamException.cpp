//
// Created by andre on 10/18/2020.
//

#include "AlreadyInStreamException.h"

#include <utility>


const char *AlreadyInStreamException::what() const noexcept {
    return "User already in stream";
}

std::ostream &operator<<(std::ostream &os, const AlreadyInStreamException &exception) {
    // TODO
    // Check weather it is a streamer or a viewer
    os << "The operation " << exception.user << " requested wasn't executed because he is already in " << exception.currStream << ".";
    return os;
}

AlreadyInStreamException::AlreadyInStreamException(std::string user,  ID streamWatching,bool viewer) : isViewer(viewer),
                                                                                                       user(std::move(user)), currStream(std::move(streamWatching)){}


