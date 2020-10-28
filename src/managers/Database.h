//
// Created by andremoreira9 on 26/10/20.
//

#ifndef FEUP_AEDA_PROJ_DATABASE_H
#define FEUP_AEDA_PROJ_DATABASE_H

class User;
class Stream;

#include <string>
#include <map>

/**
 * Class to store the data from the application
 */
class Database {
private:
    std::map<std::string, User *> users;
    std::map<ID, Stream *> streams;
public:
    Database() = default;
    /// @return A reference to the map containing the users
    std::map<std::string, User *> & getUsers(){return users;};
    /// @return A reference to the map containing the users
    std::map<ID, Stream *> & getStreams() {return streams;};
};


#endif //FEUP_AEDA_PROJ_DATABASE_H
