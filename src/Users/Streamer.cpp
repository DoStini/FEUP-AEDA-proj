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


Streamer::~Streamer() {
    if(streaming()){
        closeStream();
        // This moves the stream to finished stream, so it doesnt have problems in recursive deletion
    }

    for(const auto & curr : finishedStreams){
        streamZ->getStreamManager()->removeStream(curr);
    }
    for(const auto & curr : followedBy){
        Viewer * ptr = (Viewer *) streamZ->getSearchM()->getUser(curr);
        ptr->removeFollowStreamer(nickName);
    }
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


unsigned int Streamer::getNumViewers() {

    unsigned int views;

    Stream *ptr = streamZ->getSearchM()->getStream(currStreaming);

    if (streaming()) views += dynamic_cast<LiveStream *>(ptr)->getNumViewers();

    for (const auto &id : finishedStreams) {
        ptr = streamZ->getSearchM()->getStream(id);
        views += dynamic_cast<FinishedStream *>(ptr)->getNumViewers();
    }

    return views;
}

void Streamer::addFollower(std::string viewerNick) {
    followedBy.push_back(viewerNick);
}

void Streamer::leaveFollower(std::string viewerNick) {
    followedBy.erase(find(followedBy.begin(),followedBy.end(),viewerNick));
}

unsigned int Streamer::getNumFollowers() const {
    return followedBy.size();
}



void Streamer::closeStream() {
    if(!streaming()) throw NotInStreamException(nickName);
    finishedStreams.push_back(currStreaming);

    dynamic_cast<LiveStream *>(streamZ->getSearchM()->getStream(currStreaming))->closeStream();
    currStreaming = NULL_STREAM;
}

void Streamer::startPublicStream(std::string title, language streamLanguage, genre streamGenre, unsigned int minAge) {
    if(streaming()) throw AlreadyInStreamException(nickName, currStreaming);
    ID streamID = streamZ->getStreamManager()->createPublicStream(std::move(title), nickName, streamLanguage, streamGenre, minAge);

    currStreaming = streamID;
}

void Streamer::startPrivateStream(std::string title, language streamLanguage, genre streamGenre, unsigned int minAge,
                                  unsigned int maxNumberViewers) {
    if(streaming()) throw AlreadyInStreamException(nickName, currStreaming);
    ID streamID = streamZ->getStreamManager()->createPrivateStream(std::move(title), nickName, streamLanguage, streamGenre, minAge);

    currStreaming = streamID;
}

void Streamer::kickUser(std::string viewerNick) {
    if(!streamZ->getSearchM()->userExists(viewerNick))
        throw DoesNotExist<std::string>(viewerNick);

    auto viewer = (Viewer*) streamZ->getSearchM()->getUser(viewerNick);
    if(viewer->getCurrWatching() == currStreaming)
        viewer->leaveStream();
}

void Streamer::kickedStream() {
    if(!streaming()) throw NotInStreamException(nickName);

    currStreaming = NULL_STREAM;
}



