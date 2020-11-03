//
// Created by andre on 10/17/2020.
//

#include "Stream.h"
#include <utility>
#include "Viewer.h"

unsigned long long int Stream::lastId = 1;

Stream::Stream(std::string title, std::string language /*genres genre*/ ) :
            title(std::move(title)), streamLanguage(std::move(language)){
    Date currDate; currDate.setSystemDate();
    beginDate = currDate;
    streamId = lastId;
    lastId++;  // TODO WHEN CREATING FINISHED STREAM LASTID ALSO GETS INCREMENTED
}

void Stream::addViewer(User * viewer) {
    streamViewers.push_back(viewer);
    //likeSystem[viewer->getName()] = none;
}

void Stream::removeViewer(User *viewer) {
    streamViewers.erase(std::find(streamViewers.begin(),streamViewers.end(),viewer));
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
        Viewer * viewer = (Viewer *) streamViewers.at(i);
        viewer->leaveStream();
    }
    return nViewers;
}



bool Stream::operator<(Stream *compStream) {
    return (minAge < compStream->getMinAge());
}

const std::string &Stream::getTitle() const {
    return title;
}

const std::string &Stream::getStreamLanguage() const {
    return streamLanguage;
}

unsigned long long int Stream::getId() {
    return streamId;
}


