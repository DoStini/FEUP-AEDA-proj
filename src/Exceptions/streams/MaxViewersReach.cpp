//
// Created by adbp on 01/11/2020.
//

#include "MaxViewersReach.h"

MaxViewersReach::MaxViewersReach(ID streamId, unsigned maxViewers)
        : streamId(streamId), maxViewers(maxViewers) {}

std::ostream &operator<<(std::ostream &os, const MaxViewersReach &exception) {
    os << "Stream " << exception.streamId << " have reach is max number of viewers witch is " << exception.maxViewers;
    return os;
}

const char *MaxViewersReach::what() const noexcept {
    return "Max number of viewers have been reach.";
}