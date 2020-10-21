//
// Created by adbp on 18/10/2020.
//

#ifndef FEUP_AEDA_PROJ_PRIVATESTREAM_H
#define FEUP_AEDA_PROJ_PRIVATESTREAM_H

#include "Stream.h"
class User;

// struct used to save commentes in the stream
struct Comment{
    std::string comment;
    User * user;
};

class PrivateStream : public Stream {
public:
    PrivateStream(std::string title, std::string language, unsigned minAge = 13);
    std::string getInfo() const override;
    /**
     * Function to add a user to a whitelisted stream
     * @param user - User to be added
     */
    void addValidUser(User * user);
    /**
     * Checks if the user is in the vector of valid users
     *
     * @param user - user to check
     * @return - true if it is, otherwise false
     */
    bool isValidUser(User * user);
    /// @return Number of whitelisted viewers
    int getWhitelistSize() const;

private:
    std::vector<Comment> comments;
    std::vector<User *> whitelist;
};


#endif //FEUP_AEDA_PROJ_PRIVATESTREAM_H
