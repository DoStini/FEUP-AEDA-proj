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

std::string FinishedStream::getShorDescription() const {
    std::stringstream ss;
    ss << title << " (Stream Id: " << streamId << ")" << " ->Finished";
    return ss.str();
}

std::string FinishedStream::getLongDescription() const {
    std::stringstream ss;
    ss << "Streamed by:" << streamerNick << std::endl
       << "Star streaming: " << beginDate.getStringDate() << std::endl
       << "Language: " << streamLanguage << std::endl
       << "Genre: " << streamGenre << std::endl
       << "Final viewers: " << numViewers << std::endl
       << "Stream finished at: " << finishedDate.getStringDate();
    return ss.str();
}
