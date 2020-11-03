//
// Created by adbp on 18/10/2020.
//

#include "PublicStream.h"

#include <utility>

PublicStream::PublicStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick, unsigned minAge) :
                        LiveStream(std::move(title), streamLanguage, streamGenre,std::move(streamerNick), minAge) {}

streamType PublicStream::getStreamType() const {
    return publicType;
}

void PublicStream::addViewer(const std::string &viewerNick) {
    streamViewers.push_back(viewerNick);
}
