//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_VIEWER_H
#define FEUP_AEDA_PROJ_VIEWER_H

#include "User.h"

/**
 * Viewer class
 * Specific type of user that can watch streams and interact with them
 */
class Viewer : public User{
public:
    /**
     * Constructor when creating a new user
     *
     * @param name - Name of the user
     * @param nickName - Nickename
     * @param birthDate - Date of Birth
     */
    Viewer(std::string name, std::string nickName, const Date &birthDate);
    std::string getInfo() const;
private:
    static const unsigned minimumAge = 12;
    Stream * currWatching;
};


#endif //FEUP_AEDA_PROJ_VIEWER_H
