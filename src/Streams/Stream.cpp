//
// Created by andre on 10/17/2020.
//

#include "Stream.h"
#include <utility>
#include "Viewer.h"

Stream::Stream(std::string title, language language, genre genre ) :
            title(std::move(title)), streamLanguage(language), streamGenre(genre){
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

ID Stream::getStreamId(){
    return streamId;
}

void Stream::setStreamId(ID streamId) {
    this->streamId = streamId;
}


