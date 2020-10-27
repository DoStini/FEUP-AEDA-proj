//
// Created by adbp on 25/10/2020.
//

#include "LiveStream.h"

unsigned long long int LiveStream::lastId = 0;

LiveStream::LiveStream(std::string title, std::string language, genres genre, unsigned int minAge):
                                Stream(title,language,genre),minAge(minAge) {
    this->setStreamId(lastId);
    lastId++;
    nLikes_Dislikes.first = 0;
    nLikes_Dislikes.second = 0;
}
void LiveStream::addViewer(User * viewer) {
    streamViewers.push_back(viewer->getName());
    likeSystem[viewer->getName()] = none;
}

void LiveStream::removeViewer(User *viewer) {
    streamViewers.erase(std::find(streamViewers.begin(),streamViewers.end(),viewer->getName()));
}

unsigned int LiveStream::getNumViewers() const {
    return streamViewers.size();
}

unsigned int LiveStream::getMinAge() const {
    return minAge;
}

unsigned int LiveStream::closeStream() {
    unsigned nViewers = streamViewers.size();
    for (unsigned i = 0; i < streamViewers.size() ; i++) {
        //Viewer * viewer = (Viewer *) streamViewers.at(i);
        //viewer->leaveStream();
    }
    return nViewers;
}

int LiveStream::getLikes() const {
    return nLikes_Dislikes.first;
}

int LiveStream::getDislikes() const {
    return nLikes_Dislikes.second;
}
void LiveStream::giveLike(User * viewer) {
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

void LiveStream::giveDislike(User * viewer) {
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

void LiveStream::removeFeedBack(User *viewer) {
    std::string name = viewer->getName();
    if (likeSystem[name] == like)
        nLikes_Dislikes.first--;
    else if (likeSystem[name] == dislike)
        nLikes_Dislikes.second--;
    likeSystem[name] = none;
}