//
// Created by andre on 10/17/2020.
//

#include "Viewer.h"
#include "StreamZ.h"


Viewer::Viewer(std::string name, std::string nickName, const Date &birthDate) :
                User(name, std::move(nickName), birthDate) {
    unsigned age = getAge();

    if(age <= minimumAge)
        throw RestrictedAgeException(name, age, minimumAge);

}

userType Viewer::getUserType() const {
    return viewer;
}

void Viewer::followStreamer(std::string streamer) {

    if (std::find_if(followingStreamers.begin(), followingStreamers.end(), [streamer](std::string curr){
        return streamer == curr;
    }) != followingStreamers.end()) throw FollowStreamerException(true, streamer, nickName); // Already following

    followingStreamers.push_back(streamer);

}

void Viewer::unFollowStreamer(std::string streamer) {
    auto it = std::find_if(followingStreamers.begin(), followingStreamers.end(), [streamer](std::string curr){
        return streamer == curr;
    });
    if (it == followingStreamers.end()) throw FollowStreamerException(false, streamer, nickName); // Wasn't following

    followingStreamers.erase(it);
}

void Viewer::joinStream(ID streamID) {
    Stream * stream = streamZ->getSearchM()->getStream(streamID);

    if (watching()) throw AlreadyInStreamException(nickName, "stream1"/* stream->getName()*/);
    unsigned age = getAge();

    if(age < stream->getMinAge()) throw RestrictedAgeException(nickName, age, stream->getMinAge());

    auto * psPtr = dynamic_cast<PrivateStream *>(stream);
    if (psPtr != nullptr && !psPtr->isValidUser(this->getNickName())) throw RestrictedStreamException(stream->getTitle(), nickName);

    stream->addViewer(this);

    currWatching = stream;
}

void Viewer::leaveStream() {
    if (!watching()) throw NotInStreamException(name);
    currWatching->removeViewer(this);
    currWatching = nullptr;
}

ID Viewer::getStreamID() const {
    return 0;
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
        throw NotPrivateStreamException(currWatching->getId());

    auto * stream = (PrivateStream *) currWatching;
    stream->addComment(comment,this->getNickName());
}

bool Viewer::watching() {
    return currWatching != nullptr;
}

const std::vector<std::string> &Viewer::getFollowingStreamers() const {
    return followingStreamers;
}

const std::vector<ID> &Viewer::getHistory() const {
    return streamHistory;
}

std::string Viewer::getShortDescription() const {
    return std::__cxx11::string();
}

std::string Viewer::getLongDescription() const {
    return std::__cxx11::string();
}
