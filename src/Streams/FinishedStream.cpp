//
// Created by adbp on 26/10/2020.
//

#include "FinishedStream.h"

#include <utility>


FinishedStream::FinishedStream(std::string title, language language, genre streamGenre, int numViewers, std::string streamerNick, unsigned long long int StreamID)
                                : Stream(std::move(title),language,streamGenre,std::move(streamerNick)), numViewers(numViewers){
    this->streamId = streamId;
    Date currDate; currDate.setSystemDate();
    finishedDate = currDate;
}


streamType FinishedStream::getStreamType() const {
    return finishedType;
}