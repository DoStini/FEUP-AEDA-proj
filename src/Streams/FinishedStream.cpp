//
// Created by adbp on 26/10/2020.
//

#include "FinishedStream.h"

#include <utility>


FinishedStream::FinishedStream(std::string title, language language, genre streamGenre, int numViewers, std::string streamerNick,ID StreamID)
                                : Stream(std::move(title),language,streamGenre,std::move(streamerNick)), numViewers(numViewers){
    this->streamId = streamId;
    Date currDate; currDate.setSystemDate();
    finishedDate = currDate;
}


FinishedStream::~FinishedStream() {
    
}

streamType FinishedStream::getStreamType() const {
    return finishedType;
}

const Date &FinishedStream::getFinishedDate() const {
    return finishedDate;
}

int FinishedStream::getNumViewers() const {
    return numViewers;
}

const std::string &FinishedStream::getStreamerName() const {
    return streamerName;
}

