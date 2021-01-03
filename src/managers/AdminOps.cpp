//
// Created by andremoreira9 on 28/10/20.
//

#include <set>
#include <numeric>
#include <utility>
#include "AdminOps.h"
#include "StreamZ.h"

AdminOps::AdminOps(StreamZ *streamZ) : streamZ(streamZ) {}


/**
 * Struct used to compare two given arguments
 */
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
        if(ptr->getStreamState() == streamState::finished ) views = dynamic_cast<FinishedStream *>(ptr)->getNumViewers();
        else views = dynamic_cast<LiveStream *>(ptr)->getNumViewers();

        if ( ammViews.find(lang) != ammViews.end() )
            ammViews[lang] += views;
        else
            ammViews[lang] = views;
        its++;
    }

    if(ammViews.empty()) throw EmptyDatabaseException(false);

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
        if( ptr->getStreamState() == streamState::finished ) views = dynamic_cast<FinishedStream *>(ptr)->getNumViewers();
        else views = dynamic_cast<LiveStream *>(ptr)->getNumViewers();

        if ( ammViews.find(_genre) != ammViews.end() )
            ammViews[_genre] += views;
        else
            ammViews[_genre] = views;
        its++;
    }

    if(ammViews.empty()) throw EmptyDatabaseException(false);

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
        Stream * ptr = (*its).second;
        type = ptr->getStreamType();
        views = ptr->getNumViewers();

        if ( ammViews.find(type) != ammViews.end() )
            ammViews[type] += views;
        else
            ammViews[type] = views;

        its++;

    }

    if(ammViews.empty()) throw EmptyDatabaseException(false);

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

        if(ptr->getUserType() == userType::streamer){
            if ( ammViews.find(ptr->getNickName()) != ammViews.end() )
                ammViews[ptr->getNickName()] += dynamic_cast<Streamer *>(ptr)->getTotalViews();
            else
                ammViews[ptr->getNickName()] = dynamic_cast<Streamer *>(ptr)->getTotalViews();
        }
        its++;
    }

    if(ammViews.empty()) throw EmptyDatabaseException(true);

    std::set<std::pair<std::string, int>, comparator> res(ammViews.begin(), ammViews.end());


    std::string mostViewedNick = res.begin()->first;
    return (Streamer *) streamZ->getSearchM()->getUser(mostViewedNick);

}

long int AdminOps::numStreamsAll() {
    return streamZ->getDatabase().getStreams().size();
}

long int AdminOps::numStreams(bool activeStr) {
    auto its = streamZ->getDatabase().getStreams().begin();
    auto ite = streamZ->getDatabase().getStreams().end();
    // The state that the algorithm will
    streamState searchingState = (activeStr ? livestream : finished);
    long int acc = std::count_if(its,
                                 ite,
                                 [searchingState](const std::pair<ID, Stream *> & l1){
                                     // Compares with livestream if that's the choice. Otherwise compares with finished
                                     return l1.second->getStreamState() == searchingState;
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

    // Swap dates if reversed
    if(d2 < d1){
        Date temp;
        temp = d1;
        d1 = d2;
        d2 = temp;
    }

    auto its = streamZ->getDatabase().getStreams().begin();
    auto ite = streamZ->getDatabase().getStreams().end();
    long int acc = std::count_if(its,
                                 ite,
                                 [streamType,d1,d2](const std::pair<ID, Stream *> & l1){
                                     if(l1.second->getStreamType() == streamType){
                                         if (l1.second->getStreamState() == finished){
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

    // Swap dates if reversed
    if(d2 < d1){
        Date temp;
        temp = d1;
        d1 = d2;
        d2 = temp;
    }

    auto its = streamZ->getDatabase().getStreams().begin();
    auto ite = streamZ->getDatabase().getStreams().end();
    long int acc = std::count_if(its,
                                 ite,
                                 [d1, d2](const std::pair<ID, Stream *> & l1){
                                     if(l1.second->getStreamState() == finished){
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
        sum += its->second->getNumViewers();
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
        if( its->second->getStreamState() == finished ){
            auto * ptr = dynamic_cast<FinishedStream *>(its->second);
            if(ptr->getBeginDate() >= d1 && ptr->getFinishedDate() <= d2) {
                sum += ptr->getNumViewers();
                numStreams++;
            }
        }
        else{
            auto * ptr = dynamic_cast<LiveStream *>(its->second);
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
        streamZ->getUserM()->removeUser(std::move(nickName), true);
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

void AdminOps::changeMaxOrdersSize(size_t size) {
    streamZ->getUserM()->setOrdersSize(size);
}

unsigned AdminOps::getMaxOrdersSize() {
    return streamZ->getUserM()->getOrdersSize();
}

