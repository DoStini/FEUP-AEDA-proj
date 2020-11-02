//
// Created by andremoreira9 on 28/10/20.
//

#include <set>
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

Streamer *AdminOps::mostViewed() {
    std::unordered_map<std::string, int> ammViews;

    auto its = streamZ->getDatabase().getUsers().begin();
    auto ite = streamZ->getDatabase().getUsers().end();

    while(its != ite){

        User * ptr = its->second;

        if(ptr->getUserType() == userType::stream){
            if ( ammViews.find(ptr->getNickName()) != ammViews.end() )
                ammViews[ptr->getNickName()] += dynamic_cast<Streamer *>(ptr)->getNumViewers();
            else
                ammViews[ptr->getNickName()] = dynamic_cast<Streamer *>(ptr)->getNumViewers();
        }
        its++;
    }

    std::set<std::pair<std::string, int>, comparator> res(ammViews.begin(), ammViews.end());


    std::string mostViewedNick = res.begin()->first;
    return (Streamer *) streamZ->getSearchM()->getUser(mostViewedNick);

}

