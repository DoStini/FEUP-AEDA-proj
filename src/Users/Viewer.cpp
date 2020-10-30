//
// Created by andre on 10/17/2020.
//

#include "Viewer.h"

#include <utility>
#include "StreamZ.h"

Viewer::Viewer(std::string name, std::string nickName, const Date &birthDate) :
                User(name, std::move(nickName), birthDate) {
    if(age <= minimumAge)
        throw RestrictedAgeException(name, age, minimumAge);

}

userType Viewer::getUserType() const {
    return viewer;
}

void Viewer::followStreamer(const std::string& streamer) {

    if (std::find(followingStreamers.begin(), followingStreamers.end(), streamer) != followingStreamers.end())
        throw FollowStreamerException(true,streamer, nickName); // Already following

    followingStreamers.push_back(streamer);

}

void Viewer::unFollowStreamer(const std::string& streamer) {
    auto it = std::find(followingStreamers.begin(), followingStreamers.end(), streamer);
    if (it == followingStreamers.end())
        throw FollowStreamerException(false, streamer, nickName); // Wasn't following

    followingStreamers.erase(it);
}

void Viewer::joinStream(unsigned long long int streamID) {
    auto * stream = (LiveStream*) streamZ->getSearchM()->getStream(streamID);
    if (watching()) throw AlreadyInStreamException(nickName, currWatching);
    // TODO Is < or <= ???
    if(age < stream->getMinAge()) throw RestrictedAgeException(nickName, age, stream->getMinAge());

    auto * psPtr = dynamic_cast<PrivateStream *>(stream);
    if (psPtr != nullptr && !psPtr->isValidUser(nickName)) throw RestrictedStreamException(stream->getTitle(), nickName);

    stream->addViewer(nickName);

    currWatching = streamID;

}

void Viewer::leaveStream() {
    if (!watching()) throw NotInStreamException(name);
    auto* stream = (LiveStream*) streamZ->getSearchM()->getStream(currWatching);
    stream->removeViewer(nickName);
    currWatching = 0;
}

void Viewer::addStreamHistory(unsigned long long streamID) {
    streamHistory.push_back(streamID);
}

void Viewer::giveFeedBack(feedback fbValue) {
    auto * currStream = (LiveStream*) streamZ->getSearchM()->getStream(currWatching);

    if(!watching()) throw NotInStreamException(name);
    if (fbValue == like)
        currStream->giveLike(nickName);
    else if (fbValue == dislike)
        currStream->giveDislike(nickName);
    else if (fbValue == none)
        currStream->removeFeedBack(nickName);

}

void Viewer::giveFeedBack(std::string comment) {
    auto * currStream = (LiveStream*) streamZ->getSearchM()->getStream(currWatching);

    if(!watching()) throw NotInStreamException(name);
    if (!dynamic_cast<PrivateStream *>(currStream))
        throw NotPrivateStreamException(currStream->getTitle());

    auto * stream = (PrivateStream *) currStream;
    stream->addComment(std::move(comment),nickName);
}

bool Viewer::watching() const {
    return currWatching != 0;
}
