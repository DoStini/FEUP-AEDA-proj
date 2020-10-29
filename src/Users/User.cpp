//
// Created by andre on 10/17/2020.
//

#include "User.h"
#include "InvalidPassword.h"
#include "StreamZ.h"


User::User( std::string name, std::string nickName, const Date &birthDate) :
            name(std::move(name)), nickName(std::move(nickName)),birthDate(birthDate) {
    Date currDate; currDate.setSystemDate();
    joinedPlatformDate = currDate;
}


const std::string &User::getName() const {
    return name;
}

const std::string &User::getNickName() const {
    return nickName;
}

unsigned int User::getAge() const {
    Date currDate = Date();

    return currDate.getYearDifference(birthDate);
}

const Date &User::getBirthDate() const {
    return birthDate;
}

const Date &User::getJoinedPlatformDate() const {
    return joinedPlatformDate;
}

const std::string &User::getPassword() const {
    return password;
}

void User::changePassword(std::string newPassword) {
    if(newPassword.empty()){
        throw InvalidPassword();
    }

    password = newPassword;
}

void User::changeName(std::string newName) {
    name = newName;
}

User::~User() {
    try {
        streamZ->getDatabase().getUsers().erase(nickName);
    } catch (std::exception &e) {

    }
}

void User::setReference(StreamZ *streamZ) {
    this->streamZ = streamZ;
}
