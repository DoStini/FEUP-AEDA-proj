//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_USERMANAGER_H
#define FEUP_AEDA_PROJ_USERMANAGER_H

#include <string>


class StreamZ;

/**
 * Class to manage users, like creating and removing viewers
 */
class UserManager {
public:
    /**
    * Constructor. StreamZ needs to use to access the database and other methods
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
    void createViewer();
    /// Creates a streamer
    void createStreamer();
    /// Creates an admin
    void createAdmin();
    /// Removes a user
    void removeUser(std::string nickName);
private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_USERMANAGER_H
