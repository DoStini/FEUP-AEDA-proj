//
// Created by Nuno Alves on 28/10/2020.
//

#include "Admin.h"

userType Admin::getUserType() const {
    return admin;
}

Admin::Admin(std::string name, std::string nickName, const Date &birthDate) : User(name, nickName, birthDate) {

}
