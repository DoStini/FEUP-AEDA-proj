//
// Created by adbp on 18/10/2020.
//

#include "PrivateStream.h"

#include <utility>

#include "User.h"

PrivateStream::PrivateStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick, unsigned int minAge)
                                        : LiveStream(std::move(title), streamLanguage, streamGenre,std::move(streamerNick), minAge) {}

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
    if(std::find(whitelist.begin(),whitelist.end(),userNick) != whitelist.end())
        throw AlreadyInWhiteListException(userNick,this->getStreamId()) ;
    whitelist.push_back(userNick);
}

int PrivateStream::getWhitelistSize() const {
    return whitelist.size();
}

void PrivateStream::addComment(const std::string & text,const std::string & userNick) {
    Comment comment(text,userNick);
    comments.push_back(comment);
}

