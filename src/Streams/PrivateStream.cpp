//
// Created by adbp on 18/10/2020.
//

#include "PrivateStream.h"

#include <utility>

#include "User.h"

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
    if( isValidUser(userNick) )
        throw AlreadyInWhiteListException(userNick,this->getStreamId()) ;
    whitelist.push_back(userNick);
}

void PrivateStream::removeValidUser(const std::string &userNick) {

    if(!isValidUser(userNick))
        throw NotInWhiteListException(userNick, streamId);

    whitelist.erase(find(whitelist.begin(),whitelist.end(),userNick));
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


