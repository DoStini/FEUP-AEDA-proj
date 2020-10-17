//
// Created by andre on 10/17/2020.
//

#include "Viewer.h"

#include <utility>

Viewer::Viewer(std::string name, std::string nickName, const Date &birthDate) :
                User(name, std::move(nickName), birthDate) {
    if(age < minimumAge)
        throw RestrictedAgeException(name, age, minimumAge);

}

std::string Viewer::getInfo() const {
    return "Hey there, viewer!";
}
