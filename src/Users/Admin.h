//
// Created by adbp on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_ADMIN_H
#define FEUP_AEDA_PROJ_ADMIN_H

#include "User.h"

class Admin : public User{
    Admin(std::string name, std::string nickName, const Date &birthDate);
    ///@return - user type = streamer
    userType getUserType() const override;
};


#endif //FEUP_AEDA_PROJ_ADMIN_H
