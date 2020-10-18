//
// Created by andre on 10/17/2020.
//

#include "Viewer.h"

#include <utility>

Viewer::Viewer(std::string name, std::string nickName, const Date &birthDate) :
                User(name, std::move(nickName), birthDate) {
    if(age <= minimumAge)
        throw RestrictedAgeException(name, age, minimumAge);

}

std::string Viewer::getInfo() const {
    return "Hey there, viewer!";
}

bool Viewer::followStreamer(Streamer *streamer) {

    if (std::find_if(followingStreamers.begin(), followingStreamers.end(), [streamer](Streamer * curr){
        return *streamer == *curr;
    }) != followingStreamers.end()) return false; // Already following

    followingStreamers.push_back(streamer);

    return true;
}
