//
// Created by adbp on 18/10/2020.
//

#include "PublicStream.h"

#include <utility>

PublicStream::PublicStream(std::string title, std::string language, genres genre, unsigned minAge) :
                        LiveStream(std::move(title), std::move(language), genre, minAge) {}



std::string PublicStream::getInfo() const {
    std::ostringstream ssInfo;
    ssInfo <<"Public->  " << this->getTitle() << "       Viewers:" << this->getNumViewers() <<
                     "     Language:"<< this->getStreamLanguage() << "     Necessary age:" << this->getMinAge();
    return ssInfo.str();
}
