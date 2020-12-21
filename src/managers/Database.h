//
// Created by andremoreira9 on 26/10/20.
//

#ifndef FEUP_AEDA_PROJ_DATABASE_H
#define FEUP_AEDA_PROJ_DATABASE_H

class User;
class Stream;

#include <string>
#include <unordered_map>
#include "utils.h"
#include "BST.h"
#include "Donation.h"

/**
 * Class to store the data from the application
 */
class Database {
private:
    std::unordered_map<std::string, User *> users;
    std::unordered_map<ID, Stream *> streams;
public:
    BST<DonationItem> donations;
    Database();
    /// @return A reference to the map containing the users
    std::unordered_map<std::string, User *> & getUsers(){return users;};
    /// @return A reference to the map containing the users
    std::unordered_map<ID, Stream *> & getStreams() {return streams;};
};

#endif //FEUP_AEDA_PROJ_DATABASE_H
