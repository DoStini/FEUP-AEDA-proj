//
// Created by adbp on 26/10/2020.
//

#include "FinishedStream.h"

#include <utility>


FinishedStream::FinishedStream(std::string title, language language, genre streamGenre, int numViewers, std::string streamerName, unsigned long long int StreamID)
                                : Stream(std::move(title),language,streamGenre), numViewers(numViewers), streamerName(std::move(streamerName)) {
    this->streamID = streamID;
    Date currDate; currDate.setSystemDate();
    finishedDate = currDate;
}


streamType FinishedStream::getStreamType() const {
    return finishedType;
}