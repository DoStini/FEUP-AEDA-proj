//
// Created by andre on 10/18/2020.
//

#include "Streamer.h"

#include <utility>
#include "StreamZ.h"

Streamer::Streamer(std::string name, std::string nickName, const Date &birthDate) :
        User(name, std::move(nickName), birthDate) {
    if(age <= minimumAge)
        throw RestrictedAgeException(name, age, minimumAge);
}

userType Streamer::getUserType() const {
    return stream;
}

bool Streamer::operator==(const Streamer &str) {
    return nickName == str.nickName;
}

bool Streamer::streaming() {
    return currStreaming != NULL_STREAM;
}

ID Streamer::getStreamID() {
    return currStreaming;
}

void Streamer::addFollower(std::string viewerNick) {
    followedBy.push_back(viewerNick);
}

void Streamer::removeFollower(std::string viewerNick) {
    followedBy.erase(find(followedBy.begin(),followedBy.end(),viewerNick));
}

unsigned int Streamer::getNumFollowers() const {
    return followedBy.size();
}

unsigned int Streamer::getNumViewers() const {
    if (currStreaming == NULL_STREAM)
        throw NotInStreamException(nickName);
    auto lStream = (LiveStream*) streamZ->getSearchM()->getStream(currStreaming);
    return lStream->getNumViewers();
}

void Streamer::closeStream() {
    finishedStreams.push_back(currStreaming);
    auto lStream = (LiveStream*) streamZ->getSearchM()->getStream(currStreaming);
    lStream->closeStream();
    currStreaming = NULL_STREAM;

}

void Streamer::startPublicStream(std::string title, language streamLanguage, genre streamGenre, unsigned int minAge) {
    PublicStream newStream(std::move(title),streamLanguage,streamGenre,nickName,minAge);
    currStreaming = newStream.getStreamId();
    // TODO ADD NEW STREAM TO DATABASE
}

void Streamer::startPrivateStream(std::string title, language streamLanguage, genre streamGenre, unsigned int minAge, unsigned int maxNumberViewers) {
    PrivateStream newStream(std::move(title),streamLanguage,streamGenre,nickName,minAge,maxNumberViewers);
    currStreaming = newStream.getStreamId();
    // TODO ADD NEW STREAM TO DATABASE
}


