//
// Created by andre on 10/18/2020.
//

#include "Streamer.h"

Streamer::Streamer(std::string name, std::string nickName, const Date &birthDate) :
        User(name, std::move(nickName), birthDate) {
    if(age <= minimumAge)
        throw RestrictedAgeException(name, age, minimumAge);

}

bool Streamer::operator==(const Streamer &str) {
    return nickName == str.nickName;
}

userType Streamer::getInfo() const {
    return streamer;
}


