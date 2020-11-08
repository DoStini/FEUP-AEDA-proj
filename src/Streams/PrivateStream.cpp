//
// Created by adbp on 18/10/2020.
//

#include "PrivateStream.h"
#include <utility>
#include "StreamZ.h"

PrivateStream::PrivateStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick,
                                unsigned int minAge, unsigned int maxViewers) : LiveStream(std::move(title),
                                    streamLanguage, streamGenre,std::move(streamerNick), minAge), maxViewers(maxViewers) {}

unsigned PrivateStream::getNumberComments() {
    return comments.size();
}

streamType PrivateStream::getStreamType() const {
    return privateType;
}

bool PrivateStream::isValidUser(const std::string& userNick) {
    return (std::find(whitelist.begin(),whitelist.end(),userNick) != whitelist.end());
}

void PrivateStream::addValidUser(const std::string& userNick) {

    if(!streamZ->getSearchM()->userExists(userNick))
        throw DoesNotExist<std::string>(userNick);
    if( isValidUser(userNick) )
        throw AlreadyInWhiteListException(userNick,this->getStreamId()) ;
    whitelist.push_back(userNick);
}

void PrivateStream::removeValidUser(const std::string &userNick) {

    auto it = find(whitelist.begin(),whitelist.end(),userNick);
    if(it == whitelist.end())
        throw NotInStreamException(userNick);
    else {
        whitelist.erase(it);

        auto viewer = (Viewer *) streamZ->getSearchM()->getUser(userNick);
        if (viewer->getCurrWatching() == streamId)
            viewer->leaveStream();
    }
}

int PrivateStream::getWhitelistSize() const {
    return whitelist.size();
}

void PrivateStream::addComment(const std::string & text,const std::string & userNick) {
    Comment comment(text,userNick);
    comments.push_back(comment);
}

unsigned int PrivateStream::getMaxViewers() const {
    return maxViewers;
}

void PrivateStream::addViewer(const std::string &viewerNick) {
    if(this->getNumViewers() == maxViewers)
        throw MaxViewersReach(streamId, maxViewers);
    else
        streamViewers.push_back(viewerNick);
}

std::string PrivateStream::getShorDescription() const {
    std::stringstream ss;
    ss << title << " (Stream Id: " << streamId << ")" << " ->Private";
    return ss.str();
}

std::string PrivateStream::getLongDescription() const {
    std::stringstream ss;
    ss << "Streamed by:" << streamerNick << std::endl
       << "Star streaming: " << beginDate.getStringDate() << std::endl
       << "Language: " << streamLanguage << std::endl
       << "Genre: " << streamGenre << std::endl
       << "Necessary age to join: " << minAge << std::endl
       << "Current watching: " << streamViewers.size() << std::endl
       << "Can only have a total of " << maxViewers << " viewers watching." << std::endl
       << "Likes: " << getLikes() << " Dislikes: " << getDislikes() << std::endl
       << "My comments!";
    for(auto it=comments.begin(); it!=comments.end(); it++){
        ss << (*it);
    }
    return ss.str();
}


