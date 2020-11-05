//
// Created by andre on 10/18/2020.
//

#include "Streamer.h"

Streamer::Streamer(std::string name, std::string nickName, const Date &birthDate) :
        User(name, std::move(nickName), birthDate) {
    unsigned age = getAge();

    if(age <= minimumAge)
        throw RestrictedAgeException(name, age, minimumAge);

}

bool Streamer::operator==(const Streamer &str) {
    return nickName == str.nickName;
}

void Streamer::startPublicStream(std::string title, language streamLanguage, genre streamGenre, unsigned int minAge) {

}

void Streamer::startPrivateStream(std::string title, language streamLanguage, genre streamGenre, unsigned int minAge,
                                  unsigned int maxNumberViewers) {

}

userType Streamer::getUserType() const {
    return streamer;
}

ID Streamer::getStreamID() {
    return currStreaming;
}

void Streamer::kickUser(std::string viewerNick) {

}

bool Streamer::streaming() {
    return currStreaming != NULL_STREAM;
}


