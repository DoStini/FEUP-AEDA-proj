//
// Created by adbp on 25/10/2020.
//

#include "LiveStream.h"
#include "StreamZ.h"


ID LiveStream::lastId = NULL_STREAM;

LiveStream::LiveStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick, unsigned minAge):
                                Stream(std::move(title),streamLanguage,streamGenre,std::move(streamerNick)),minAge(minAge) {
    streamId = ++lastId;
    nLikes_Dislikes.first = 0;
    nLikes_Dislikes.second = 0;
}

LiveStream::~LiveStream() {
    Streamer * streamer = (Streamer *) streamZ->getSearchM()->getUser(streamerNick);
    streamer->kickedStream();
    for(const auto & v : streamViewers){
        Viewer * ptr = (Viewer *) streamZ->getSearchM()->getUser(v);
        ptr->kickedStream();
    }
    streamZ->getUserM()->removeHistoryElemFromUser(streamId);
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
    int nViewers = this->getNumViewers();

    auto *fStream = new FinishedStream(this->getTitle(),this->getStreamLanguage(),
                                       this->getGenre(),nViewers,
                                       this->getStreamerNick(),streamId, this->getStreamType());

    fStream->setStreamZ(streamZ);
    ID id =streamId;
    for (unsigned i = 0; i < streamViewers.size() ; i++) {
        Viewer * viewer = (Viewer *) streamZ->getSearchM()->getUser(streamViewers.at(i));
        viewer->kickedStream();
    }
    streamZ->getDatabase().getStreams().erase(id);
    streamZ->getDatabase().getStreams().insert(std::pair<ID, Stream *> (id, fStream));

    return nViewers;
}

unsigned int LiveStream::getLikes() const {
    return nLikes_Dislikes.first;
}

unsigned int LiveStream::getDislikes() const {
    return nLikes_Dislikes.second;
}
void LiveStream::giveLike(const std::string& viewerNick) {
    if(likeSystem.find(viewerNick) == likeSystem.end())
        likeSystem[viewerNick] = none;
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
    if(likeSystem.find(viewerNick) == likeSystem.end())
        likeSystem[viewerNick] = none;
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
    if(likeSystem.find(viewerNick) == likeSystem.end())
        likeSystem[viewerNick] = none;
    if (likeSystem[viewerNick] == like)
        nLikes_Dislikes.first--;
    else if (likeSystem[viewerNick] == dislike)
        nLikes_Dislikes.second--;
    likeSystem[viewerNick] = none;
}

bool LiveStream::operator<(LiveStream *compStream) {
    return (minAge < compStream->getMinAge());
}



streamState LiveStream::getStreamState() const {
    return livestream;
}

LiveStream::LiveStream() : Stream() {

}

void LiveStream::addBonusLikes(int likes) {
    nLikes_Dislikes.first += likes;
}



