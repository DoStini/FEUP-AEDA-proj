//
// Created by adbp on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_ADMIN_H
#define FEUP_AEDA_PROJ_ADMIN_H

#include "User.h"

/**
 * Viewer class
 * Specific type of user that can watch streams and interact with them
 */
class Admin : public User{
public:
    /**
     * Admin Constructor
     * @param name Name of the admin
     * @param nickName Nickname of the admin
     * @param password Password of the admin
     * @param birthDate Birth Date of the admin
     */
    Admin(std::string name, std::string nickName,std::string password, const Date &birthDate);
    /// Empty constructor - Use when reading from file
    Admin();
    /// Returns the user type
    ///@return - user type = admin
    userType getUserType() const override;
    /// Returns a short description with info about the user
    ///@return Short description
    std::string getShortDescription() const override;
    /// Returns a long description with info about the user
    ///@return Long description
    std::string getLongDescription(bool seePassword = false) const override;
    /// Not applicable to admin
    std::string getFollowDetails() const override;
    /// Not applicable to admin
    std::string getHistoryDetails() const override;
    /**
     * Writing user info to file
     * @param ff Current file stream
     */
    void writeToFile(std::ofstream &ff) override;
    /**
     * Reading user info from file
     * @param ff Current file stream
    */
    void readFromFile(std::ifstream &ff) override;
};


#endif //FEUP_AEDA_PROJ_ADMIN_H
