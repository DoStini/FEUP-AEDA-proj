//
// Created by andremoreira9 on 27/10/20.
//

#include "SearchManager.h"
#include "StreamZ.h"

User *SearchManager::getUser(std::string userNick) const {
    User * val;
    try{
        val = streamZ->getDatabase().getUsers().at(userNick);
    } catch (const std::out_of_range &e) {
        throw DoesNotExist<std::string>(userNick);
    }
    return val;
}

Stream *SearchManager::getStream(ID streamID) const {
    Stream * val;
    try{
        val = streamZ->getDatabase().getStreams().at(streamID);
    } catch (const std::exception &e) {
        throw DoesNotExist<ID>(streamID);
    }
    return val;
}

SearchManager::SearchManager(StreamZ *streamZ) : streamZ(streamZ) {}

void SearchManager::listLiveStreams(std::vector<LiveStream *> &streams, const std::string &streamName, unsigned minAge,
                                    const std::vector<genre> &genres, const std::vector<language> &langs) const{

}

void SearchManager::listLiveStreamsByStreamers(std::vector<LiveStream *> &streams,
                                               const std::vector<std::string> &streamerNick)const {

}

void SearchManager::listUsers(std::vector<User *> &users, const std::string &name) const{
}

