//
// Created by andremoreira9 on 26/10/20.
//

#ifndef FEUP_AEDA_PROJ_DATABASE_H
#define FEUP_AEDA_PROJ_DATABASE_H

class User;
class Stream;

#include <string>
#include <map>

class Database {
private:
    std::map<std::string, User *> users;
    std::map<long long int, Stream *> streams;
public:
    Database = default;
    std::map<std::string, User *> & getUsers(){return users;};
    std::map<long long int, Stream *> & getStreams() {return streams;};
};


#endif //FEUP_AEDA_PROJ_DATABASE_H
