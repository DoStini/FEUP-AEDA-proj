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

void Admin::writeToFile(std::ofstream &ff) {
    int numNames = 0;
    std::string counter;
    std::stringstream temp(name);
    while (temp >> counter) numNames ++;
    ff << numNames << " , " << name << " , " << nickName << " , " << password << " , "
       << birthDate.getStringDate() << " , " << joinedPlatformDate.getStringDateTime() << std::endl;
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
    birthDate = Date(temp);
    ff >> sep;

    // Clearing the string stream
    ss.str(std::string());

    ff >> temp; ss << temp << " "; // Building date and hour/minute
    ff >> temp; ss << temp; // Building date and hour/minute


    joinedPlatformDate = Date(ss.str());
}

std::string Admin::getShorDescription() const {
    return std::string();
}

std::string Admin::getLongDescription() const {
    return std::string();
}

std::string Admin::getFollowDetails() const {
    return std::string();
}

std::string Admin::getHistoryDetails() const {
    return std::string();
}
