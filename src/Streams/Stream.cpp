//
// Created by andre on 10/17/2020.
//

#include "Stream.h"
#include <utility>

Stream::Stream(std::string title, std::string language, unsigned int minAge) :
            title(std::move(title)), streamLanguage(std::move(language)), minAge(minAge) {
    Date currDate; currDate.setSystemDate();
    beginDate = currDate;
    liveStream = true;
}

void Stream::addViewer(User * viewer) {
    streamViewers.push_back(viewer);
}

unsigned int Stream::getNumViewers() const {
    return streamViewers.size();
}

unsigned int Stream::getMinAge() const {
    return minAge;
}

unsigned int Stream::closeStream() {
    // go through all the viewers and leave the stream
    liveStream = false;
    return streamViewers.size();
}

void Stream::giveLike() {
    nLikes++;
}

void Stream::giveDislike() {
    nDislikes++;
}

void Stream::removeLike() {
    nLikes--;
}

void Stream::removeDislike() {
    nDislikes--;
}

bool Stream::operator<(Stream *compStream) {
    return (minAge < compStream->getMinAge());
}

const std::string &Stream::getTitle() const {
    return title;
}


