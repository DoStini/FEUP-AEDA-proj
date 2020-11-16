//
// Created by adbp on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_ADMIN_H
#define FEUP_AEDA_PROJ_ADMIN_H

#include "User.h"

class Admin : public User{
public:

    Admin(std::string name, std::string nickName,std::string password, const Date &birthDate);

    Admin();

    ///@return - user type = streamer
    userType getUserType() const override;
    ///@return Short description
    std::string getShorDescription() const override;
    ///@return Long description
    std::string getLongDescription() const override;
    /// Not applicable
    std::string getFollowDetails() const override;
    /// Not applicable
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
