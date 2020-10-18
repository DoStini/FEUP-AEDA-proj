//
// Created by adbp on 18/10/2020.
//

#ifndef FEUP_AEDA_PROJ_PRIVATESTREAM_H
#define FEUP_AEDA_PROJ_PRIVATESTREAM_H

#include "Stream.h"

// struct used to save commentes in the stream
struct Comment{
    std::string comment;
    User * user;
};

class privateStream : public Stream {
public:
    /**
     * Checks if the user is in the vector of valid users
     *
     * @param user - user to check
     * @return - true if it is, otherwise false
     */
    bool isValidUser(User * user);

private:
    std::vector<Comment> comments;
    std::vector<User *> validUsers;
};


#endif //FEUP_AEDA_PROJ_PRIVATESTREAM_H
