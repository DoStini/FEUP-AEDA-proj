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

std::string PublicStream::getShorDescription() const {
    std::stringstream ss;
    ss << title << " (Stream Id: " << streamId << ")" << " ->Public";
    return ss.str();
}

std::string PublicStream::getLongDescription() const {
    std::stringstream ss;
    ss << "Streamed by:" << streamerNick << std::endl
    << "Star streaming: " << beginDate.getStringDate() << std::endl
    << "Language: " << streamLanguage << std::endl
    << "Genre: " << streamGenre << std::endl
    << "Necessary age to join: " << minAge << std::endl
    << "Current watching: " << streamViewers.size() << std::endl
    << "Likes: " << getLikes() << " Dislikes: " << getDislikes();
    return ss.str();
}
