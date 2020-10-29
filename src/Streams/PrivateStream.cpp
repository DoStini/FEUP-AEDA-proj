//
// Created by adbp on 18/10/2020.
//

#include "PrivateStream.h"

#include <utility>

#include "User.h"

PrivateStream::PrivateStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick, unsigned int minAge)
                                        : LiveStream(std::move(title), streamLanguage, streamGenre,streamerNick, minAge) {}
unsigned PrivateStream::getNumberComments() {
    return comments.size();
}

streamType PrivateStream::getStreamType() const {
    return privateType;
}

bool PrivateStream::isValidUser(User *user) {
    std::string nick = user->getNickName();
    return std::find_if(
            whitelist.begin(),
            whitelist.end(),
            [nick](User * usr){return usr->getNickName() == nick;}
            ) != whitelist.end();
}

void PrivateStream::addValidUser(User * user) {
    std::string nick = user->getNickName();
    if(std::find_if(
            whitelist.begin(),
            whitelist.end(),
            [nick](User * usr){return usr->getNickName() == nick;}
        ) != whitelist.end()) throw std::string("Duplicate Exception");
    // TODO CREATE DUPLICATE EXCEPTION TO USE AS FOLLOW STREAMER EXCEPTION AS WELL
    whitelist.push_back(user);
}

int PrivateStream::getWhitelistSize() const {
    return whitelist.size();
}

void PrivateStream::addComment(std::string text, User *viewer) {
    Comment comment(text,viewer->getName());
    comments.push_back(comment);
}

