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
    nLikes_Dislikes.first = 0;
    nLikes_Dislikes.second = 0;
}

void Stream::addViewer(User * viewer) {
    streamViewers.push_back(viewer);
    likeSystem[viewer->getName()] = none;
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

int Stream::getLikes() const {
    return nLikes_Dislikes.first;
}

const int Stream::getDislikes() const {
    return nLikes_Dislikes.second;
}

unsigned int Stream::closeStream() {
    unsigned nViewers = streamViewers.size();
    for (unsigned i = 0; i < streamViewers.size() ; i++) {
        Viewer * viewer = (Viewer *) streamViewers.at(i);
        viewer->leaveStream();
    }
    liveStream = false;
    return nViewers;
}

void Stream::giveLike(User * viewer) {
    std::string name = viewer->getName();
    if(likeSystem[name] == none) {
        likeSystem[name] = like;
        nLikes_Dislikes.first++;
    }
    else if(likeSystem[name] == dislike){
        likeSystem[name] = like;
        nLikes_Dislikes.first++;
        nLikes_Dislikes.second--;
    }
}

void Stream::giveDislike(User * viewer) {
    std::string name = viewer->getName();
    if(likeSystem[name] == none) {
        likeSystem[name] = dislike;
        nLikes_Dislikes.second++;
    }
    else if(likeSystem[name] == like){
        likeSystem[name] = dislike;
        nLikes_Dislikes.first--;
        nLikes_Dislikes.second++;
    }
}

void Stream::removeFeedBack(User *viewer) {
    std::string name = viewer->getName();
    if (likeSystem[name] == like)
        nLikes_Dislikes.first--;
    else if (likeSystem[name] == dislike)
        nLikes_Dislikes.second--;
    likeSystem[name] = none;
}

bool Stream::operator<(Stream *compStream) {
    return (minAge < compStream->getMinAge());
}

const std::string &Stream::getTitle() const {
    return title;
}


