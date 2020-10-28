//
// Created by adbp on 18/10/2020.
//

#include "PrivateStream.h"

#include <utility>

#include "User.h"

PrivateStream::PrivateStream(std::string title, languages language, genres genre, unsigned int minAge)
                                        : LiveStream(std::move(title), std::move(language), genre, minAge) {}
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

std::string PrivateStream::getInfo() const {
    std::ostringstream ssInfo;
    ssInfo <<"Private->  " << this->getTitle() << "       Viewers:" << this->getNumViewers() <<
           "     Language:"<< this->getStreamLanguage() << "     Necessary age:" << this->getMinAge();
    return ssInfo.str();
}

void PrivateStream::addComment(std::string text, User *viewer) {
    Comment comment(text,viewer->getName());
    comments.push_back(comment);
}

