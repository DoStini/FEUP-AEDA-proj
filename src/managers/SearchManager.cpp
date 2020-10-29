//
// Created by andremoreira9 on 27/10/20.
//

#include "SearchManager.h"
#include "StreamZ.h"


SearchManager::SearchManager(StreamZ *streamZ) : streamZ(streamZ) {}


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



/*
void SearchManager::listLiveStreams(std::vector<LiveStream *> &streams) {

    if(!streams.empty()) streams.clear();

    auto p1 = streamZ->getDatabase().getStreams().begin(),
            p2 = streamZ->getDatabase().getStreams().end();

    while(p1!=p2){
        if((*p1).second->getStreamType() == privateType || (*p1).second->getStreamType() == publicType)
            streams.push_back(dynamic_cast<LiveStream *>((*p1).second));
        p1++;
    }
}
*/
void SearchManager::listUsers(std::vector<User *> &users, const std::string& name) {

    if(!users.empty()) users.clear();

    auto p1 = streamZ->getDatabase().getUsers().begin(),
            p2 = streamZ->getDatabase().getUsers().end();

    while(p1!=p2){
        if((*p1).second->getName() == name || name.empty())
            users.push_back(((*p1).second));
        p1++;
    }
}

void SearchManager::listLiveStreams(std::vector<LiveStream *> &streams, const std::string &streamName,
                                    const std::vector<genre> &genres, const std::vector<language> &langs) {

    // Empties the vector if not empty
    if(!streams.empty()) streams.clear();


    bool checkGenres = !genres.empty(),
            checkLangs = !langs.empty();

    // Iterator to the database map
    auto it1 = streamZ->getDatabase().getStreams().begin(),
            it2 = streamZ->getDatabase().getStreams().end();

    // Loop to iterate over the map
    while(it1 != it2){
        Stream * ptr = (*it1).second; // Getting the current stream pointer

        // Is a livestream?
        if(ptr->getStreamType() == privateType || ptr->getStreamType() == publicType){
            genre strGrn = ptr->getGenre();
            language strLang = ptr->getStreamLanguage();

            // Checks if the current stream verifies all 3 requests (or those asked)
            if( (ptr->getTitle() == streamName || streamName.empty()) &&
                // Only verifies the vector if it is not empty (if the user wants to specify genre)
                (!checkGenres || std::find_if(genres.begin(),
                                              genres.end(),
                                              [strGrn](genre gnr){return gnr == strGrn;}) != genres.end()) &&
                // Only verifies the vector if it is not empty (if the user wants to specify genre)
                (!checkLangs || std::find_if(langs.begin(),
                                             langs.end(),
                                             [strLang](language lang){return lang == strLang;}) != langs.end()))
            {
                streams.push_back(dynamic_cast<LiveStream *>((*it1).second));
            }
        }
        it1++;
    }
}

void SearchManager::listLiveStreamsByStreamers(std::vector<LiveStream *> &streams,
                                               const std::vector<std::string> &streamerNick) {
    // Empties the vector if not empty
    if(!streams.empty()) streams.clear();

    for( const auto & nick : streamerNick){
        Streamer * str = dynamic_cast<Streamer *>(getUser(nick));
        // Converting the user, if it is a viewer, str stores nullptr
        // If the the streaming is currently streaming, finds and stores the respective stream
        if (str != nullptr && str->streaming())
            streams.push_back(dynamic_cast<LiveStream *>(getStream(str->getStreamID())));
    }
}



