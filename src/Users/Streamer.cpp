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
    if (currStreaming == 0)
        throw NotInStreamException(nickName);
    else return currStreaming;
}


unsigned int Streamer::getTotalViews() {

    unsigned int views;

    Stream *ptr = streamZ->getSearchM()->getStream(currStreaming);

    if (streaming()) views += dynamic_cast<LiveStream *>(ptr)->getNumViewers();

    for (const auto &id : finishedStreams) {
        ptr = streamZ->getSearchM()->getStream(id);
        views += dynamic_cast<FinishedStream *>(ptr)->getNumViewers();
    }

    return views;
}

unsigned int Streamer::getStreamViewers() {
    if(!streaming())
        throw NotInStreamException(nickName);

    auto ptr =(LiveStream *) streamZ->getSearchM()->getStream(currStreaming);
    return ptr->getNumViewers();
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
    if(!streaming())
        throw NotInStreamException(nickName);

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

std::string Streamer::getShorDescription() const {
    std::stringstream  ss;
    ss << name << " (Nickname: " << nickName << ")" << " ->Streamer";
    return ss.str();
}

std::string Streamer::getLongDescription() const {
    std::stringstream  ss;
    ss << "My password is " << password << " hope you enjoy my account :)\n"
    << "I was born in " << birthDate.getStringDate() << " so i have " << age << " years.\n"
    << "Have join StreamZ in: " << joinedPlatformDate.getStringDate()
    << "Current have " << getNumFollowers() << " followers.\n";
    if(currStreaming == NULL_STREAM){
        ss << "Right now i am not streaming.\n";
    }
    else{
        ss << "Right now i am streaming:\n"
        << streamZ->getSearchM()->getStream(currStreaming)->getShorDescription() << std::endl;
    }
    ss << "I have streamed a total of " << finishedStreams.size() << " streams.\n";
    return ss.str();
}

std::string Streamer::getFollowDetails() const {
    std::stringstream  ss;
    ss << "My followers are:\n";
    for(const auto & it : followedBy){
        ss << it << std::endl;
    }
    return ss.str();
}

std::string Streamer::getHistoryDetails() const {
    std::stringstream  ss;
    ss << "My finished streams are:\n";
    for(const auto & it : finishedStreams){
        ss << streamZ->getSearchM()->getStream(it)->getShorDescription() << std::endl;
    }
    return ss.str();
}



