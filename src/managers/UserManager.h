//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_USERMANAGER_H
#define FEUP_AEDA_PROJ_USERMANAGER_H

#include <string>
#include <Date.h>
#include "AlreadyExists.h"
#include "Viewer.h"
#include "Streamer.h"
#include "Admin.h"

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
    /// @return If an admin is already registered
    /// Creates a viewer
    void createViewer(const std::string& name, const std::string& nickName, const Date &birthDate);
    /// Creates a streamer
    void createStreamer(std::string name, std::string nickName, const Date &birthDate);
    /// Creates an admin
    void createAdmin(std::string name, std::string nickName, const Date &birthDate);
    /// Removes a user
    void removeUser(std::string nickName);
private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_USERMANAGER_H
