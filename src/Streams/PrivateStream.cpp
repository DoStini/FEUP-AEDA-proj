//
// Created by adbp on 18/10/2020.
//

#include "PrivateStream.h"

#include <utility>

#include "User.h"

PrivateStream::PrivateStream(std::string title, std::string language, unsigned int minAge) : LiveStream(std::move(title),language,
                                                                                                    minAge) {}
unsigned PrivateStream::getNumberComments() {
    return comments.size();
}

bool PrivateStream::isValidUser(const std::string& nick) {
    return true;
}

void PrivateStream::addValidUser(const std::string& user) {
}

int PrivateStream::getWhitelistSize() const {
    return whitelist.size();
}

void PrivateStream::addComment(const std::string& text, const std::string & userNick) {
}

streamType PrivateStream::getStreamType() const {
    return privateType;
}

void PrivateStream::removeValidUser(const std::string &userNick) {

}

std::string PrivateStream::getLongDescription() const {
    return std::__cxx11::string();
}

std::string PrivateStream::getShortDescription() const {
    return std::__cxx11::string();
}

