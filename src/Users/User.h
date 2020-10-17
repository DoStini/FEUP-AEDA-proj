//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_USER_H
#define FEUP_AEDA_PROJ_USER_H

#include <string>
#include "Date.h"
#include "RestrictedAgeException.h"
#include "Stream.h"


/**
 * User master class
 */
class User {
public:
    /**
     * Constructor when creating a new user
     *
     * @param name - Name of the user
     * @param nickName - Nickename
     * @param birthDate - Date of Birth
     */
    User(std::string name, std::string nickName, const Date &birthDate);
    /**
     * Constructor when loading user from a file database
     * TEMPORARY - IF WE READ FROM BINARY WE DONT NEED THIS
     *
     * @param name - Name
     * @param nickName - Nickname
     * @param birthDate - Date of birth
     * @param joinedPlatDate - Date when user joined Streamz
     */
    User(std::string name, std::string nickName, const Date &birthDate, const Date &joinedPlatDate);

    /// @return Name
    const std::string &getName() const;
    /// @return Nickname
    const std::string &getNickName() const;
    /// @return Age
    unsigned int getAge() const;
    /// @return BirthDate
    const Date &getBirthDate() const;
    /// @return Date which user joined StreamZ
    const Date &getJoinedPlatformDate() const;

    virtual std::string getInfo() const = 0;

protected:
    std::string name;
    std::string nickName;
    unsigned age;
    Date birthDate;
    /// Date when user joined Streamz
    Date joinedPlatformDate;
};


#endif //FEUP_AEDA_PROJ_USER_H
