//
// Created by andre on 10/17/2020.
//

#include "Stream.h"
#include <utility>
#include "Viewer.h"

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
    unsigned nViewers = streamViewers.size();
    for (unsigned i = 0; i < streamViewers.size() ; i++) {
        Viewer * viewer;
        viewer = (Viewer *) streamViewers.at(i);
        viewer->leaveStream();
    }
    liveStream = false;
    return nViewers;
}

void Stream::giveLike(User * viewer) {

}

void Stream::giveDislike(User * viewer) {

}

void Stream::removeLike(User * viewer) {

}

void Stream::removeDislike(User * viewer) {

}

bool Stream::operator<(Stream *compStream) {
    return (minAge < compStream->getMinAge());
}

const std::string &Stream::getTitle() const {
    return title;
}


