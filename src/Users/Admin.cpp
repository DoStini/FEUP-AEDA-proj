//
// Created by adbp on 28/10/2020.
//

#include "Admin.h"

#include <utility>

userType Admin::getUserType() const {
    return admin;
}

Admin::Admin(std::string name, std::string nickName, const Date &birthDate) : User(std::move(name), std::move(nickName), birthDate) {
}

Admin::Admin() : User(){

}

void Admin::writeToFile(std::ofstream &ofstream) {

}

void Admin::readFromFile(std::ifstream &ifstream) {

}
