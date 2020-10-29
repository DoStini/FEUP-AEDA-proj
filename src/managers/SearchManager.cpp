//
// Created by andremoreira9 on 27/10/20.
//

#include "SearchManager.h"
#include "StreamZ.h"

User *SearchManager::getUser(std::string userNick) {
    User * val;
    try{
        val = streamZ->getDatabase().getUsers().at(userNick);
    } catch (const std::exception &e) {
        throw DoesNotExist<std::string>(userNick);
    }
    return val;
}

Stream *SearchManager::getStream(ID streamID) {
    Stream * val;
    try{
        val = streamZ->getDatabase().getStreams().at(streamID);
    } catch (const std::exception &e) {
        throw DoesNotExist<ID>(streamID);
    }
    return val;
}


SearchManager::SearchManager(StreamZ *streamZ) : streamZ(streamZ) {}

void SearchManager::listLiveStreams(std::vector<LiveStream *> &streams) {

    auto p1 = streamZ->getDatabase().getStreams().begin(),
            p2 = streamZ->getDatabase().getStreams().end();

    while(p1!=p2){
        if((*p1).second->getStreamType() == privateType || (*p1).second->getStreamType() == publicType)
            streams.push_back(dynamic_cast<LiveStream *>((*p1).second));
        p1++;
    }
}


