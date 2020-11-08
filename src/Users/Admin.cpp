//
// Created by Nuno Alves on 28/10/2020.
//

#include "Admin.h"

userType Admin::getUserType() const {
    return admin;
}

Admin::Admin(std::string name, std::string nickName, const Date &birthDate) : User(name, nickName, birthDate) {

}

std::string Admin::getShortDescription() const {
    return std::__cxx11::string();
}

std::string Admin::getLongDescription() const {
    return std::__cxx11::string();
}
