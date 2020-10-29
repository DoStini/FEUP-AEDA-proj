//
// Created by adbp on 18/10/2020.
//

#include "PublicStream.h"

#include <utility>

PublicStream::PublicStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick, unsigned minAge) :
                        LiveStream(std::move(title), streamLanguage, streamGenre,streamerNick, minAge) {}

streamType PublicStream::getStreamType() const {
    return publicType;
}