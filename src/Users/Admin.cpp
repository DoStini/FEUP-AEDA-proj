//
// Created by adbp on 28/10/2020.
//

#include "Admin.h"
#include <iomanip>
#include <iostream>

#include <utility>

userType Admin::getUserType() const {
    return admin;
}

Admin::Admin(std::string name, std::string nickName,std::string password, const Date &birthDate)
    : User(std::move(name), std::move(nickName),std::move(password), birthDate) {
}

Admin::Admin() : User(){

}

void Admin::writeToFile(std::ofstream &ff) {
    int numNames = 0;
    std::string counter;
    std::stringstream temp(name);
    while (temp >> counter) numNames ++;
    ff << numNames << " , " << name << " , " << nickName << " , " << password << " , "
       << birthDate.getStringDate() << " , " << joinedPlatformDate.getStringDateTime() << " , " << std::endl;
}

void Admin::readFromFile(std::ifstream &ff) {
    int numNames;
    char sep;

    std::string temp;
    std::stringstream ss;

    ff >> numNames >> sep;

    for (int i = 0; i < numNames; ++i) {
        ff >> temp;
        ss << temp << " ";
    }

    name = ss.str();

    ff >> sep >> nickName >> sep >> password >> sep;

    ff >> temp;
    birthDate = Date(temp, true);
    ff >> sep;

    // Clearing the string streamer
    ss.str(std::string());

    ff >> temp; ss << temp << " "; // Building date and hour/minute
    ff >> temp >> sep; ss << temp; // Building date and hour/minute

    joinedPlatformDate = Date(ss.str(), true);
}

std::string Admin::getLongDescription(bool seePassword) const {
    std::stringstream  ss;
      ss << "My name is " << name << std::endl
         << "My nickname is " << nickName << std::endl
         << "I am an admin" << std::endl
         << "I was born in " << birthDate.getStringDate() << " so i have " << age() << " years.\n"
       << "Joined StreamZ in: " << joinedPlatformDate.getStringDate();
    return ss.str();
}

std::string Admin::getFollowDetails() const {
    return std::string();
}

std::string Admin::getHistoryDetails() const {
    return std::string();
}

std::string Admin::getShortDescription() const {
    std::stringstream  ss1, ss2;
    ss1 << "| nick: " << nickName;
    ss2 << std::setw(20) << std::left << name << std::setw(45) << std::left << ss1.str() << std::setw(12) << std::left << "| Admin";
    return ss2.str();
}
