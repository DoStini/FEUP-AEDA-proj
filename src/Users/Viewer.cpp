//
// Created by andre on 10/17/2020.
//

#include "Viewer.h"


Viewer::Viewer(std::string name, std::string nickName, const Date &birthDate) :
                User(name, std::move(nickName), birthDate) {
    if(age <= minimumAge)
        throw RestrictedAgeException(name, age, minimumAge);

}

std::string Viewer::getInfo() const {
    std::stringstream ss; ss << "Viewer: " << name << ". Nickname: " << nickName << ". Age: " << age << ".";
    return ss.str();
}

void Viewer::followStreamer(Streamer *streamer) {

    if (std::find_if(followingStreamers.begin(), followingStreamers.end(), [streamer](Streamer * curr){
        return *streamer == *curr;
    }) != followingStreamers.end()) throw FollowStreamerException(true, streamer->getNickName(), nickName); // Already following

    followingStreamers.push_back(streamer);

}

void Viewer::unFollowStreamer(Streamer *streamer) {
    auto it = std::find_if(followingStreamers.begin(), followingStreamers.end(), [streamer](Streamer * curr){
        return *streamer == *curr;
    });
    if (it == followingStreamers.end()) throw FollowStreamerException(false, streamer->getNickName(), nickName); // Wasn't following

    followingStreamers.erase(it);
}

void Viewer::joinStream(Stream *stream) {
    // TODO When stream is ready
    if (watching()) throw AlreadyInStreamException(nickName, "stream1"/* stream->getName()*/);
    // Stream.verifyUser throw Exception
    // Stream.minimumAge throw RequiredAgeException
    // Stream.addUser
    currWatching = stream;
}

void Viewer::leaveStream() {
    if (!watching()) throw NotInStreamException(name);
    currWatching = nullptr;
}

void Viewer::giveFeedBack() {
    if(!watching()) throw NotInStreamException(name);
    // Stream.like()
}

void Viewer::giveFeedBack(std::string comment) {
    if(!watching()) throw NotInStreamException(name);
    // Dynamic cast to verify type of stream
    // Throw Exception
}

bool Viewer::watching() {
    return currWatching != nullptr;
}
