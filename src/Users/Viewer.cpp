//
// Created by andre on 10/17/2020.
//

#include "Viewer.h"

#include <utility>
#include "StreamZ.h"

Viewer::Viewer(std::string name, std::string nickName, const Date &birthDate) :
                User(name, std::move(nickName), birthDate) {
    if(age() <= minimumAge)
        throw RestrictedAgeException(name, (int) age(), minimumAge);

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
    if(age() < stream->getMinAge()) throw RestrictedAgeException(nickName, (int) age(), stream->getMinAge());

    auto * stream =streamZ->getSearchM()->getStream(streamID);

    streamType type = stream->getStreamType();

    if (type == finishedType)
        throw RestrictedStreamException(stream->getTitle(), nickName);

    auto liveStream = (LiveStream *) stream;
    // TODO Is < or <= ???
    if(age < liveStream->getMinAge()) throw RestrictedAgeException(nickName, age, liveStream->getMinAge());

    if(type == privateType)
    {
        auto * pStream = (PrivateStream *) stream;
        if (!pStream->isValidUser(nickName))
            throw RestrictedStreamException(stream->getTitle(), nickName);
    }

    liveStream->addViewer(nickName);
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
    if (currStream->getStreamType() != privateType)
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
        auto * ptr =  dynamic_cast<LiveStream *>(streamZ->getSearchM()->getStream(currWatching));
        ptr->removeViewer(nickName);
    }
    for(const auto & streamer : followingStreamers){
        Streamer * ptr = dynamic_cast<Streamer *>(streamZ->getSearchM()->getUser(streamer));
        ptr->leaveFollower(nickName);
    }
    streamZ->getStreamManager()->removeViewerFromWhitelists(nickName);
}

bool Viewer::isFollowing(std::string &streamer) {
    return false;
}


Viewer::Viewer() {}

std::string Viewer::getShorDescription() const {
    std::stringstream  ss;
    ss << name << " (Nickname: " << nickName << ")" << " ->Viewer";
    return ss.str();
}

std::string Viewer::getLongDescription() const {
    std::stringstream  ss;
    ss << "My password is " << password << " hope you enjoy my account :)\n"
       << "I was born in " << birthDate.getStringDate() << " so i have " << age << " years.\n"
       << "Have join StreamZ in: " << joinedPlatformDate.getStringDate()
       << "Follow " << followingStreamers.size() << " streamers.\n"
       << "They are:\n";
    for(const auto & it : followingStreamers){
        ss << it << std::endl;
    }
    if(currWatching == NULL_STREAM){
        ss << "Right now i am watching nothing.\n";
    }
    else{
        ss << "Right now i am watching:\n"
           << streamZ->getSearchM()->getStream(currWatching)->getShorDescription() << std::endl;
    }
    ss << "I have seen a total of " << streamHistory.size() << " streams.\n";
    return ss.str();
}

std::string Viewer::getFollowDetails() const {
    std::stringstream  ss;
    ss << "The streamers that i follow are:\n";
    for(const auto & it : followingStreamers){
        ss << it << std::endl;
    }
    return ss.str();
}

std::string Viewer::getHistoryDetails() const {
    std::stringstream  ss;
    ss << "I have participate in the following streams: \n";
    for(const auto & it : streamHistory){
        ss << streamZ->getSearchM()->getStream(it)->getShorDescription() << std::endl;
    }
    return ss.str();
}

void Viewer::readFromFile(std::ifstream &ff) {

    int numNames;
    char sep;

    std::string temp;
    std::stringstream ss;

    ff >> numNames >> sep;

    for (int i = 0; i < numNames; ++i) {
        ff >> temp;
        ss << temp;
    }

    name = ss.str();

    ff >> sep >> nickName >> sep >> password >> sep;

    ff >> temp;
    birthDate = Date(temp);
    ff >> sep;

    // Clearing the string stream
    ss.str(std::string());

    ff >> temp; ss << temp << " "; // Building date and hour/minute
    ff >> temp; ss << temp; // Building date and hour/minute

    joinedPlatformDate = Date(ss.str());

    int size;
    ID id;

    ff >> sep >> currWatching >> sep >> size >> sep;

    for (int i = 0; i < size; ++i) {
        ff >> temp >> sep;
        followingStreamers.push_back(temp);
    }

    ff >> size >> sep;

    for (int i = 0; i < size; ++i) {
        ff >> id >> sep;
        streamHistory.push_back(id);
    }
}

void Viewer::writeToFile(std::ofstream &ff) {

    int numNames = 0;
    std::string counter;
    std::stringstream temp(name);
    while (temp >> counter) numNames ++;

    ff << numNames << " , " << name << " , " << nickName << " , " << password << " , "
        << birthDate.getStringDate() << " , " << joinedPlatformDate.getStringDateTime()
        << " , " << currWatching << " , "
        << followingStreamers.size() << " , ";

    for(const auto & str : followingStreamers){
        ff << str << " , ";
    }

    ff << streamHistory.size() << " , ";

    for(const auto & id : streamHistory){
        ff << id << " , ";
    }
    ff << std::endl;
}
