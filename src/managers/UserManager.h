//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_USERMANAGER_H
#define FEUP_AEDA_PROJ_USERMANAGER_H

#include <string>
#include "Date.h"


class StreamZ;

/**
 * Class to manage users, like creating and removing viewers
 */
class UserManager {
public:
    /**
     * Constructor. StreamZ needs to be used by the class to access the database and other methods
     * @param streamZ - Main class pointer
     */
    UserManager(StreamZ *streamZ);
    /**
     * Function to check if a user exists or not
     * @param nickName - Nickname of the user
     * @return user exists or not
     */
    bool userExists(std::string nickName);
    /// Creates a viewer
    void createViewer(std::string userName, std::string nickName, Date date, std::string password);
    /// Creates a streamer
    void createStreamer(std::string userName, std::string nickName, Date date, std::string password);
    /// Creates an admin
    void createAdmin(std::string userName, std::string nickName, Date date, std::string password);
    /// Removes a user
    void removeUser(std::string nickName);

    void changePassword(const std::string &basicString);

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_USERMANAGER_H
