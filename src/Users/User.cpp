//
// Created by andre on 10/17/2020.
//

#include "User.h"


User::User( std::string name, std::string nickName, const Date &birthDate) :
            name(std::move(name)), nickName(std::move(nickName)),birthDate(birthDate) {
    Date currDate; currDate.setSystemDate();
    joinedPlatformDate = currDate;
    age = currDate.getYearDifference(birthDate);
}


const std::string &User::getName() const {
    return name;
}

const std::string &User::getNickName() const {
    return nickName;
}

unsigned int User::getAge() const {
    return age;
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

bool User::changePassword(std::string newPassword) {
    if(newPassword == password || newPassword.empty()){
        return false; // Later throw an exception
    }
    password = newPassword;
    return true;
}
