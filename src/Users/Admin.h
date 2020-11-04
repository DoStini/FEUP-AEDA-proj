//
// Created by Nuno Alves on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_ADMIN_H
#define FEUP_AEDA_PROJ_ADMIN_H

#include "User.h"

class Admin : public User{
public:
    /**
     * Constructor when creating a new user
     * Throws a RestrictedAgeException if the user is not allowed to create an account
     * @param name - Name of the user
     * @param nickName - Nickename
     * @param birthDate - Date of Birth
     */
    Admin(std::string name, std::string nickName, const Date &birthDate);
    /**
     * Info about the Admin
     * @return UserType containing info about the admin
     */
    userType getUserType() const override;
};


#endif //FEUP_AEDA_PROJ_ADMIN_H
