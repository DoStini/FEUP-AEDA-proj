//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_USER_H
#define FEUP_AEDA_PROJ_USER_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#include "utils.h"
#include "Date.h"
#include "RestrictedAgeException.h"
#include "FollowStreamerException.h"
#include "AlreadyInStreamException.h"
#include "NotInStreamException.h"
#include "RestrictedStreamException.h"
#include "Stream.h"

class StreamZ;

enum UserType {
    viewer, streamer, admin
};

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

    virtual ~User();

    /**
     * Changes the user's password
     *
     * @param newPassword the new password
     * @throws InvalidPassword if the password was invalid.
     */
    void changePassword(std::string newPassword);

    /**
     * Changes the user's name.
     *
     * @param newName the new name of the user.
     */
    void changeName(std::string newName);

    void setReference(StreamZ * streamZ);

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
    /// @return UserType info about the user
    virtual UserType getInfo() const = 0;
    /// @return password of the user
    const std::string &getPassword() const;

protected:
    std::string name;
    /// Used to login and other id related stuff
    std::string nickName;
    /// Used to login
    std::string password;
    Date birthDate;
    /// Date when user joined Streamz
    Date joinedPlatformDate;
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_USER_H
