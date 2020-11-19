//
// Created by andre on 10/17/2020.
//

#include "Stream.h"
#include "StreamZ.h"

Stream::Stream(std::string title, language language, genre genre, std::string streamerNick ) :
            title(std::move(title)), streamLanguage(language), streamGenre(genre), streamerNick(std::move(streamerNick)){
    Date currDate; currDate.setSystemDate();
    beginDate = currDate;
}


const std::string &Stream::getTitle() const {
    return title;
}

const language &Stream::getStreamLanguage() const {
    return streamLanguage;
}

const Date &Stream::getBeginDate() const {
    return beginDate;
}

genre Stream::getGenre() const {
    return streamGenre;
}

ID Stream::getStreamId() const{
    return streamId;
}

void Stream::setStreamId(ID id) {
    this->streamId = id;
}

void Stream::setStreamZ(StreamZ *pStreamZ) {
    this->streamZ = pStreamZ;
}

const std::string &Stream::getStreamerNick() const {
    return streamerNick;
}

Stream::Stream() = default;

