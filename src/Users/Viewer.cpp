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

void Viewer::followStreamer(const std::string& streamerNick) {
    if(!streamZ->getSearchM()->userExists(streamerNick))
        throw DoesNotExist<std::string>(streamerNick);

    if (std::find(followingStreamers.begin(), followingStreamers.end(), streamerNick) != followingStreamers.end())
        throw FollowStreamerException(true,streamerNick, nickName); // Already following

    followingStreamers.push_back(streamerNick);

    auto streamer = (Streamer*) streamZ->getSearchM()->getUser(streamerNick);
    streamer->addFollower(nickName);
}

void Viewer::unFollowStreamer(const std::string& streamerNick) {
    auto it = std::find(followingStreamers.begin(), followingStreamers.end(), streamerNick);
    if (it == followingStreamers.end())
        throw FollowStreamerException(false, streamerNick, nickName); // Wasn't following

    followingStreamers.erase(it);

    auto streamer = (Streamer*) streamZ->getSearchM()->getUser(streamerNick);
    streamer->leaveFollower(nickName);
}


void Viewer::removeFollowStreamer(const std::string & streamerNick) {
    auto it = std::find(followingStreamers.begin(), followingStreamers.end(), streamerNick);

    followingStreamers.erase(it);
}

void Viewer::joinStream(ID streamID) {
    if(!streamZ->getSearchM()->streamExists(streamID))
        throw DoesNotExist<ID>(streamID);
    else if(watching()) throw AlreadyInStreamException(nickName, currWatching);

    auto * stream = (LiveStream*) streamZ->getSearchM()->getStream(streamID);
    // TODO Is < or <= ???
    if(age < stream->getMinAge()) throw RestrictedAgeException(nickName, age, stream->getMinAge());

    streamType type = stream->getStreamType();

    if (type == finishedType)
        throw RestrictedStreamException(stream->getTitle(), nickName);
    else if(type == privateType)
    {
        auto * pStream = (PrivateStream *) stream;
        if (!pStream->isValidUser(nickName))
            throw RestrictedStreamException(stream->getTitle(), nickName);
    }

    stream->addViewer(nickName);

    currWatching = streamID;

}

void Viewer::leaveStream() {
    if (!watching()) throw NotInStreamException(name);
    auto* stream = (LiveStream*) streamZ->getSearchM()->getStream(currWatching);
    stream->removeViewer(nickName);
    streamHistory.push_back(currWatching);
    currWatching = NULL_STREAM;
}

void Viewer::kickedStream() {
    if (!watching()) throw NotInStreamException(name);
    streamHistory.push_back(currWatching);
    currWatching = NULL_STREAM;
}

void Viewer::addStreamHistory(ID streamID) {
    streamHistory.push_back(streamID);
}

void Viewer::removeStreamHistory(ID streamID) {
    streamHistory.erase(std::find(streamHistory.begin(), streamHistory.end(), streamID));
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

void Viewer::giveFeedBack(const std::string& comment) {
    auto * currStream = (LiveStream*) streamZ->getSearchM()->getStream(currWatching);

    if(!watching()) throw NotInStreamException(name);
    if (!dynamic_cast<PrivateStream *>(currStream))
        throw NotPrivateStreamException(currStream->getStreamId());

    auto * stream = (PrivateStream *) currStream;
    stream->addComment(comment,nickName);
}

bool Viewer::watching() const {
    return currWatching != 0;
}

bool Viewer::isInStreamHistory(ID streamID) {
    return !(find(streamHistory.begin(),streamHistory.end(),streamID) == streamHistory.end());
}

ID Viewer::getCurrWatching() const {
    return currWatching;
}

Viewer::~Viewer() {
    if(watching()){
        LiveStream * ptr = (LiveStream *) streamZ->getSearchM()->getStream(currWatching);
        ptr->removeViewer(nickName);
    }
    for(const auto & streamer : followingStreamers){
        Streamer * ptr = (Streamer *) streamZ->getSearchM()->getUser(streamer);
        ptr->leaveFollower(nickName);
    }
    streamZ->getStreamManager()->removeViewerFromWhitelists(nickName);
}

bool Viewer::isFollowing(std::string &streamer) {
    return false;
}


