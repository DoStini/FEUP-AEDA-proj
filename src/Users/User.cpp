//
// Created by andre on 10/17/2020.
//

#include "User.h"
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



const Date &User::getBirthDate() const {
    return birthDate;
}

const Date &User::getJoinedPlatformDate() const {
    return joinedPlatformDate;
}

const std::string &User::getPassword() const {
    return password;
}

bool User::changePassword(const std::string& newPassword) {
    if(newPassword == password || newPassword.empty()){
        return false; // Later throw an exception
    }
    password = newPassword;
    return true;
}

void User::setStreamZ(StreamZ *streamZ) {
    this->streamZ = streamZ;
}

unsigned User::age() {
    Date currDate; currDate.setSystemDate();
    return currDate.getYearDifference(birthDate);;
}
