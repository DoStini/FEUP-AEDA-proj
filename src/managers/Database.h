//
// Created by andremoreira9 on 26/10/20.
//

#ifndef FEUP_AEDA_PROJ_DATABASE_H
#define FEUP_AEDA_PROJ_DATABASE_H

class User;
class Stream;

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "utils.h"
#include "Streamer.h"

/**
 * Class to store the data from the application
 */
class Database {
private:
    std::unordered_map<std::string, User *> users;
    std::unordered_map<ID, Stream *> streams;
    std::unordered_set<User *, streamerHash, streamerHash> streamers;
public:
    Database() = default;
    /// @return A reference to the map containing the users
    std::unordered_map<std::string, User *> & getUsers(){return users;};
    /// @return A reference to the map containing the users
    std::unordered_map<ID, Stream *> & getStreams() {return streams;};
};


#endif //FEUP_AEDA_PROJ_DATABASE_H
