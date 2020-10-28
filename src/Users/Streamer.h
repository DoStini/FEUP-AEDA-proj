//
// Created by andre on 10/18/2020.
//



#ifndef FEUP_AEDA_PROJ_STREAMER_H
#define FEUP_AEDA_PROJ_STREAMER_H

#include "User.h"

/**
 * Class Streamer
 * The class that contains information and methods related to the streamer
 */
class Streamer : public User {
public:
    /**
    * Constructor when creating a new user
    * Throws a RestrictedAgeException if the user is not allowed to create an account
    * @param name - Name of the user
    * @param nickName - Nickname
    * @param birthDate - Date of Birth
    */
    Streamer(std::string name, std::string nickName, const Date &birthDate);
    std::string getInfo() const override;
    ///@return - user type = streamer
    userType getUserType() const;
    bool operator == (const Streamer & str);
private:
    static const unsigned minimumAge = STREAMER_MIN_AGE;
};


#endif //FEUP_AEDA_PROJ_STREAMER_H
