//
// Created by andremoreira9 on 28/10/20.
//

#include <set>
#include <numeric>
#include "AdminOps.h"
#include "StreamZ.h"

AdminOps::AdminOps(StreamZ *streamZ) : streamZ(streamZ) {}



struct comparator{
    template<class T>
    bool operator()(const T& t1, const T& t2){
        return t1.second > t2.second;
    }
};


language AdminOps::rankViewsLang(bool reversed) {
    std::unordered_map<language, int> ammViews;

    auto its = streamZ->getDatabase().getStreams().begin();
    auto ite = streamZ->getDatabase().getStreams().end();

    language lang;
    int views;

    while(its != ite){
        lang = (*its).second->getStreamLanguage();
        Stream * ptr = (*its).second;
        if(ptr->getStreamType() == streamType::finishedType ) views = dynamic_cast<FinishedStream *>(ptr)->getNumViewers();
        else views = dynamic_cast<LiveStream *>(ptr)->getNumViewers();

        if ( ammViews.find(lang) != ammViews.end() )
            ammViews[lang] += views;
        else
            ammViews[lang] = views;
        its++;
    }

    std::set<std::pair<language, int>, comparator> res(ammViews.begin(), ammViews.end());

    auto last = res.end(); --last;

    return !reversed
            ? res.begin()->first
            : last->first;
}

genre AdminOps::rankViewsGenres(bool reversed) {
    std::unordered_map<genre, int> ammViews;

    auto its = streamZ->getDatabase().getStreams().begin();
    auto ite = streamZ->getDatabase().getStreams().end();

    genre _genre;
    int views;

    while(its != ite){
        _genre = (*its).second->getGenre();
        Stream * ptr = (*its).second;
        if(ptr->getStreamType() == streamType::finishedType ) views = dynamic_cast<FinishedStream *>(ptr)->getNumViewers();
        else views = dynamic_cast<LiveStream *>(ptr)->getNumViewers();

        if ( ammViews.find(_genre) != ammViews.end() )
            ammViews[_genre] += views;
        else
            ammViews[_genre] = views;
        its++;
    }

    std::set<std::pair<genre, int>, comparator> res(ammViews.begin(), ammViews.end());

    auto last = res.end(); --last;

    return !reversed
           ? res.begin()->first
           : last->first;
}

streamType AdminOps::rankViewsTypes(bool reversed) {
    std::unordered_map<streamType, int> ammViews;

    auto its = streamZ->getDatabase().getStreams().begin();
    auto ite = streamZ->getDatabase().getStreams().end();

    streamType type;
    int views;

    while(its != ite){
        type = (*its).second->getStreamType();

        if ( ammViews.find(type) != ammViews.end() )
            ammViews[type] += views;
        else
            ammViews[type] = views;
        its++;
    }

    std::set<std::pair<streamType, int>, comparator> res(ammViews.begin(), ammViews.end());

    auto last = res.end(); --last;

    return !reversed
           ? res.begin()->first
           : last->first;
}


Streamer *AdminOps::mostViewed() {
    std::unordered_map<std::string, int> ammViews;

    auto its = streamZ->getDatabase().getUsers().begin();
    auto ite = streamZ->getDatabase().getUsers().end();

    while(its != ite){

        User * ptr = its->second;

        if(ptr->getUserType() == userType::stream){
            if ( ammViews.find(ptr->getNickName()) != ammViews.end() )
                ammViews[ptr->getNickName()] += dynamic_cast<Streamer *>(ptr)->getTotalViews();
            else
                ammViews[ptr->getNickName()] = dynamic_cast<Streamer *>(ptr)->getTotalViews();
        }
        its++;
    }

    std::set<std::pair<std::string, int>, comparator> res(ammViews.begin(), ammViews.end());


    std::string mostViewedNick = res.begin()->first;
    return (Streamer *) streamZ->getSearchM()->getUser(mostViewedNick);

}

long int AdminOps::numStreamsAll() {
    return streamZ->getDatabase().getStreams().size();
}

long int AdminOps::numStreams() {
    auto its = streamZ->getDatabase().getStreams().begin();
    auto ite = streamZ->getDatabase().getStreams().end();
    long int acc = std::count_if(its,
                                 ite,
                                 [](const std::pair<ID, Stream *> & l1){
                                     return l1.second->getStreamType() != finishedType;
                                 });
    return acc;
}

long int AdminOps::numStreams(streamType streamType) {
    auto its = streamZ->getDatabase().getStreams().begin();
    auto ite = streamZ->getDatabase().getStreams().end();
    long int acc = std::count_if(its,
                                 ite,
                                 [streamType](const std::pair<ID, Stream *> & l1){
                                    return l1.second->getStreamType() == streamType;
                                 });
    return acc;

}

long int AdminOps::numStreams(streamType streamType, Date d1, Date d2) {
    auto its = streamZ->getDatabase().getStreams().begin();
    auto ite = streamZ->getDatabase().getStreams().end();
    long int acc = std::count_if(its,
                                 ite,
                                 [streamType,d1,d2](const std::pair<ID, Stream *> & l1){
                                     if(l1.second->getStreamType() == streamType){
                                         if (l1.second->getStreamType() == finishedType){
                                             FinishedStream * ptr = (FinishedStream *) l1.second;
                                             return ptr->getBeginDate() >= d1 && ptr->getFinishedDate() <= d2;
                                         }
                                         else{
                                             LiveStream * ptr = (LiveStream *) l1.second;
                                             return ptr->getBeginDate() >= d1;
                                         }
                                     }
                                     else return false;
                                 });
    return acc;
}

long int AdminOps::numStreams(Date d1, Date d2) {
    auto its = streamZ->getDatabase().getStreams().begin();
    auto ite = streamZ->getDatabase().getStreams().end();
    long int acc = std::count_if(its,
                                 ite,
                                 [d1, d2](const std::pair<ID, Stream *> & l1){
                                     if(l1.second->getStreamType() == finishedType){
                                         FinishedStream * ptr = (FinishedStream *) l1.second;
                                         return ptr->getBeginDate() >= d1 && ptr->getFinishedDate() <= d2;
                                     }
                                     else{
                                         LiveStream * ptr = (LiveStream *) l1.second;
                                         return ptr->getBeginDate() >= d1;
                                     }
                                 });
    return acc;
}


float AdminOps::medianViewsStream() {
    auto its = streamZ->getDatabase().getStreams().begin();
    auto ite = streamZ->getDatabase().getStreams().end();
    long int sum = 0;
    while(its != ite){
        if( its->second->getStreamType() == finishedType ){
            FinishedStream * ptr = dynamic_cast<FinishedStream *>(its->second) ;
            sum += ptr->getNumViewers();

        }
        else{
            LiveStream * ptr = dynamic_cast<LiveStream *>(its->second);
            sum += ptr->getNumViewers();
        }
        its++;
    }

    if(numStreamsAll() == 0) return 0;

    return (float)sum/(float)numStreamsAll();
}

float AdminOps::medianViewsStream(Date d1, Date d2) {
    auto its = streamZ->getDatabase().getStreams().begin();
    auto ite = streamZ->getDatabase().getStreams().end();
    long int numStreams = 0, sum = 0;

    while(its != ite){
        if( its->second->getStreamType() == finishedType ){
            FinishedStream * ptr = dynamic_cast<FinishedStream *>(its->second);
            if(ptr->getBeginDate() >= d1 && ptr->getFinishedDate() <= d2) {
                sum += ptr->getNumViewers();
                numStreams++;
            }
        }
        else{
            LiveStream * ptr = dynamic_cast<LiveStream *>(its->second);
            if (ptr->getBeginDate() <= d2 && ptr->getBeginDate() >= d1) {
                sum += ptr->getNumViewers();
                numStreams++;
            }
        }
        its++;
    }
    if(numStreams == 0) return 0;
    return (float)sum/(float)numStreams;
}

void AdminOps::removeUser(std::string nickName) {
    try{
        streamZ->getUserM()->removeUser(nickName);
    } catch (const DoesNotExist<std::string> &e) {
        throw e;
    }
}

void AdminOps::removeStream(ID streamID) {
    try{
        streamZ->getStreamManager()->removeStream(streamID);
    } catch (const DoesNotExist<ID> &e) {
        throw e;
    }
}





