//
// Created by adbp on 18/10/2020.
//

#include "PublicStream.h"

#include <utility>

PublicStream::PublicStream(std::string title, language streamLanguage, genre streamGenre, unsigned minAge) :
                        LiveStream(std::move(title), streamLanguage, streamGenre, minAge) {}



std::string PublicStream::getInfo() const {
    std::ostringstream ssInfo;
    ssInfo <<"Public->  " << this->getTitle() << "       Viewers:" << this->getNumViewers() <<
                     "     Language:"<< this->getStreamLanguage() << "     Necessary age:" << this->getMinAge();
    return ssInfo.str();
}

streamType PublicStream::getStreamType() const {
    return publicType;
}