//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_USER_H
#define FEUP_AEDA_PROJ_USER_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <istream>

#include "utils.h"
#include "Date.h"
#include "RestrictedAgeException.h"
#include "FollowStreamerException.h"
#include "AlreadyInStreamException.h"
#include "NotInStreamException.h"
#include "RestrictedStreamException.h"
#include "Stream.h"


class StreamZ;

/**
 * User master class
 */
class User {
public:
    User() = default;
    /**
     * Constructor when creating a new user
     *
     * @param name - Name of the user
     * @param nickName - Nickename
     * @param password - password of the user
     * @param birthDate - Date of Birth
     */
    User(std::string name, std::string nickName,std::string password ,const Date &birthDate);

    User(const std::string & nick);
    virtual ~User(){};

    /// @return Name
    const std::string &getName() const;

    /// @return Nickname
    const std::string &getNickName() const;

    /// @return BirthDate
    const Date &getBirthDate() const;

    /// @return Date which user joined StreamZ
    const Date &getJoinedPlatformDate() const;

    /// @return password of the user
    const std::string &getPassword() const;

    /// @return Age
    unsigned age() const;
    ///@return - give us the user type
    virtual userType getUserType() const = 0;

    /// Returns a short description with info about the user
    ///@return Short description
    virtual std::string getShortDescription() const = 0;
    /// Returns a long description with info about the user
    ///@return Long description
    virtual std::string getLongDescription(bool seePassword = false) const = 0;
    /// Info about the streamer/viewer's following details
    /// @return - string with all the followers/following
    virtual std::string getFollowDetails() const = 0;
    /// Info about the streamer/viewer's
    /// @return - string with all the streamer history/finished
    virtual std::string getHistoryDetails() const = 0;

    ///@param streamZ - pointer to streamZ
    void setStreamZ(StreamZ *streamZ);

    /**
     * Change password of the user
     *
     * @param newPassword
     * @return - true if succeed else false
     */
    bool changePassword(const std::string& newPassword);

    /**
     * Change name of the user
     *
     * @param newName
     */
    void changeName(const std::string &newName);

    /**
     * Function to read a User to the files
     * @param ifstream
     */
    virtual void readFromFile(std::ifstream & ff ) = 0;
    /**
     * Function to write a User to the files
     * @param ofstream
     */
    virtual void writeToFile(std::ofstream  & ff ) = 0;
protected:
    /// General class that have all the info
    StreamZ * streamZ = nullptr;
    /// User name
    std::string name;
    /// Used to login and other id related stuff
    std::string nickName;
    /// Used to login
    std::string password;
    /// Birth date
    Date birthDate;
    /// Date when user joined Streamz
    Date joinedPlatformDate;
};


#endif //FEUP_AEDA_PROJ_USER_H
