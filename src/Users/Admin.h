//
// Created by adbp on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_ADMIN_H
#define FEUP_AEDA_PROJ_ADMIN_H

#include "User.h"

class Admin : public User{
public:
    Admin(std::string name, std::string nickName, const Date &birthDate);

    Admin();

    ///@return - user type = streamer
    userType getUserType() const override;
    void writeToFile(std::ofstream &ff) override;
    void readFromFile(std::ifstream &ff) override;
};


#endif //FEUP_AEDA_PROJ_ADMIN_H
