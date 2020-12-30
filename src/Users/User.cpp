//
// Created by andre on 10/17/2020.
//

#include "User.h"
#include "InvalidPassword.h"
#include "StreamZ.h"

#include <utility>
#include "StreamZ.h"

User::User( std::string name, std::string nickName,std::string password, const Date &birthDate) :
            name(std::move(name)), nickName(std::move(nickName)),password(std::move(password)), birthDate(birthDate) {
    Date currDate; currDate.setSystemDate();
    joinedPlatformDate = currDate;
}

User::User(const std::string & nick) : nickName(nick) {}

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

void User::changeName(const std::string & newName) {
    name = newName;
}

void User::setStreamZ(StreamZ *streamZ) {
    this->streamZ = streamZ;
}

unsigned User::age() const{
    Date currDate; currDate.setSystemDate();
    return currDate.getYearDifference(birthDate);
}




