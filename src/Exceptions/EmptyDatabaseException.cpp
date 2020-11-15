//
// Created by andremoreira9 on 08/11/20.
//

#include "EmptyDatabaseException.h"

EmptyDatabaseException::EmptyDatabaseException(bool users) : users(users) {}

const char *EmptyDatabaseException::what() const noexcept {
    return "Empty database";
}

std::ostream &operator<<(std::ostream &os, const EmptyDatabaseException &database) {
    os << (database.users ? "User's" : "Streams'") << " database empty.";
    return os;
}
