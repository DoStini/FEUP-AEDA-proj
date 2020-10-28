//
// Created by andre on 10/17/2020.
//

#include "Stream.h"
#include <utility>
#include "Viewer.h"

Stream::Stream(std::string title, languages language, genres genre ) :
            title(std::move(title)), streamLanguage(std::move(language)){
    Date currDate; currDate.setSystemDate();
    beginDate = currDate;
}

const std::string &Stream::getTitle() const {
    return title;
}

const languages &Stream::getStreamLanguage() const {
    return streamLanguage;
}

const Date &Stream::getBeginDate() const {
    return beginDate;
}

genres Stream::getGenre() const {
    return genre;
}

unsigned long long int Stream::getStreamId() const {
    return streamId;
}

void Stream::setStreamId(unsigned long long int streamId) {
    this->streamId = streamId;
}


