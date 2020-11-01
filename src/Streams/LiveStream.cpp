//
// Created by adbp on 25/10/2020.
//

#include "LiveStream.h"
#include "StreamZ.h"

#include <utility>

ID LiveStream::lastId = 0;

LiveStream::LiveStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick, unsigned int minAge):
                                Stream(std::move(title),streamLanguage,streamGenre,std::move(streamerNick)),minAge(minAge) {
    streamId = ++lastId;
    nLikes_Dislikes.first = 0;
    nLikes_Dislikes.second = 0;
}
void LiveStream::addViewer(const std::string& viewerNick) {
    streamViewers.push_back(viewerNick);
    likeSystem[viewerNick] = none;
}

void LiveStream::removeViewer(const std::string& viewerNick) {
    streamViewers.erase(std::find(streamViewers.begin(),streamViewers.end(),viewerNick));
}

unsigned int LiveStream::getNumViewers() const {
    return streamViewers.size();
}

unsigned int LiveStream::getMinAge() const {
    return minAge;
}

unsigned int LiveStream::closeStream() {
    unsigned nViewers = this->getNumViewers();
    FinishedStream fStream(this->getTitle(),this->getStreamLanguage(),this->getGenre(),nViewers,this->getStreamerNick(),streamId);
    for (unsigned i = 0; i < streamViewers.size() ; i++) {
        Viewer * viewer = (Viewer *) streamZ->getSearchM()->getUser(streamViewers.at(i));
        viewer->leaveStream();
        viewer->addStreamHistory(streamId);

    }
    //TODO REMOVER LIVE STREAM DA DATABASE E ADICIONAR FINISHED STREAM
    return nViewers;
}

int LiveStream::getLikes() const {
    return nLikes_Dislikes.first;
}

int LiveStream::getDislikes() const {
    return nLikes_Dislikes.second;
}
void LiveStream::giveLike(const std::string& viewerNick) {
    if(likeSystem[viewerNick] == none) {
        likeSystem[viewerNick] = like;
        nLikes_Dislikes.first++;
    }
    else if(likeSystem[viewerNick] == dislike){
        likeSystem[viewerNick] = like;
        nLikes_Dislikes.first++;
        nLikes_Dislikes.second--;
    }
}

void LiveStream::giveDislike(const std::string& viewerNick) {
    if(likeSystem[viewerNick] == none) {
        likeSystem[viewerNick] = dislike;
        nLikes_Dislikes.second++;
    }
    else if(likeSystem[viewerNick] == like){
        likeSystem[viewerNick] = dislike;
        nLikes_Dislikes.first--;
        nLikes_Dislikes.second++;
    }
}

void LiveStream::removeFeedBack(const std::string& viewerNick) {
    if (likeSystem[viewerNick] == like)
        nLikes_Dislikes.first--;
    else if (likeSystem[viewerNick] == dislike)
        nLikes_Dislikes.second--;
    likeSystem[viewerNick] = none;
}

bool LiveStream::operator<(LiveStream *compStream) {
    return (minAge < compStream->getMinAge());
}