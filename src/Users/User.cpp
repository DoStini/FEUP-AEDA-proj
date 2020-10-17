//
// Created by andre on 10/17/2020.
//

#include "User.h"

#include <utility>

User::User( std::string name, std::string nickName, const Date &birthDate) :
            name(std::move(name)), nickName(std::move(nickName)),birthDate(birthDate) {
    Date currDate; currDate.setSystemDate();
    joinedPlatformDate = currDate;
    // Calculate user age
}

User::User( std::string name, std::string nickName,  const Date &birthDate,  const Date &joinedPlatDate) :
            name(std::move(name)), nickName(std::move(nickName)),birthDate(birthDate){
    // Calculate user age
}
