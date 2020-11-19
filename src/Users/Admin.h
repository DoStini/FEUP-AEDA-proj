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

    Admin(std::string name, std::string nickName,std::string password, const Date &birthDate);

    Admin();

    ///@return - user type = streamer
    userType getUserType() const override;
    ///@return Short description
    std::string getShortDescription() const override;
    ///@return Long description
    std::string getLongDescription(bool seePassword = false) const override;
    /// Not applicable
    std::string getFollowDetails() const override;
    /// Not applicable
    std::string getHistoryDetails() const override;
    /**
     * Writing user info to file
     * @param ff Current file streamer
     */
    void writeToFile(std::ofstream &ff) override;
    /**
     * Reading user info from file
     * @param ff Current file streamer
    */
    void readFromFile(std::ifstream &ff) override;
};


#endif //FEUP_AEDA_PROJ_ADMIN_H
