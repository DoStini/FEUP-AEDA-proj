//
// Created by andre on 10/17/2020.
//

#include "Viewer.h"


Viewer::Viewer(std::string name, std::string nickName, const Date &birthDate) :
                User(name, std::move(nickName), birthDate) {
    if(age <= minimumAge)
        throw RestrictedAgeException(name, age, minimumAge);

}

userType Viewer::getInfo() const {
    return viewer;
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
    if (watching()) throw AlreadyInStreamException(nickName, "stream1"/* stream->getName()*/);
    // TODO Is < or <= ???
    if(age < stream->getMinAge()) throw RestrictedAgeException(nickName, age, stream->getMinAge());

    auto * psPtr = dynamic_cast<PrivateStream *>(stream);
    if (psPtr != nullptr && !psPtr->isValidUser(this)) throw RestrictedStreamException(stream->getTitle(), nickName);

    stream->addViewer(this);

    currWatching = stream;
}

void Viewer::leaveStream() {
    if (!watching()) throw NotInStreamException(name);
    currWatching->removeViewer(this);
    currWatching = nullptr;
}

void Viewer::giveFeedBack(feedback fbValue) {
    if(!watching()) throw NotInStreamException(name);
    /*
    if (fbValue == like)
        currWatching->giveLike(this);
    else if (fbValue == dislike)
        currWatching->giveDislike(this);
    else if (fbValue == none)
        currWatching->removeFeedBack(this);
        */
}

void Viewer::giveFeedBack(std::string comment) {
    if(!watching()) throw NotInStreamException(name);
    if (!dynamic_cast<PrivateStream *>(currWatching))
        throw NotPrivateStreamException(currWatching->getTitle());

    auto * stream = (PrivateStream *) currWatching;
    stream->addComment(comment,this);
}

bool Viewer::watching() {
    return currWatching != nullptr;
}
