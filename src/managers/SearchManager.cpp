//
// Created by andremoreira9 on 27/10/20.
//

#include "SearchManager.h"
#include "StreamZ.h"



SearchManager::SearchManager(StreamZ *streamZ) : streamZ(streamZ) {}


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
void SearchManager::listUsers(std::vector<User *> &users, const std::string& name) const {

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
                                    unsigned minAge,
                                    const std::vector<genre> &genres, const std::vector<language> &langs)  const{

    // Empties the vector if not empty
    if(!streams.empty()) streams.clear();


    bool checkGenres = !genres.empty(),
            checkLangs = !langs.empty();

    // Iterator to the database map
    auto it1 = streamZ->getDatabase().getStreams().begin(),
            it2 = streamZ->getDatabase().getStreams().end();

    // Loop to iterate over the map
    while(it1 != it2){
        Stream * ptr = (*it1).second; // Getting the current streamer pointer

        // Is a livestream?
        if(ptr->getStreamState() == livestream){
            // Checks if the current streamer verifies all 3 requests (or those asked)
            if( (streamName.empty() || ptr->getTitle() == streamName) &&
                // Verifies age restriction
                dynamic_cast<LiveStream *>(ptr)->getMinAge() >= minAge &&
                // Only verifies the vector if it is not empty (if the user wants to specify genre)
                (!checkGenres || checkParam<genre>( genres,ptr->getGenre()) ) &&
                // Only verifies the vector if it is not empty (if the user wants to specify genre)
                (!checkLangs || checkParam<language>(langs, ptr->getStreamLanguage())))
            {
                streams.push_back(dynamic_cast<LiveStream *>((*it1).second));
            }
        }
        it1++;
    }
}

void SearchManager::listLiveStreamsByStreamers(std::vector<LiveStream *> &streams,
                                               const std::vector<std::string> &streamerNick) const {
    // Empties the vector if not empty
    if(!streams.empty()) streams.clear();

    for( const auto & nick : streamerNick){
        Streamer * str = dynamic_cast<Streamer *>(getUser(nick));
        // Converting the user, if it is a viewer, str stores nullptr
        // If the the streaming is currently streaming, finds and stores the respective streamer
        if (str != nullptr && str->streaming())
            streams.push_back(dynamic_cast<LiveStream *>(getStream(str->getStreamID())));
    }
}

bool SearchManager::userExists(std::string nick) const {
    std::transform(nick.begin(), nick.end(), nick.begin(), ::tolower);
    std::unordered_map<std::string, User *> map = streamZ->getDatabase().getUsers();
    bool fuck = map.find(nick) != map.end();
    return fuck;
}

bool SearchManager::streamExists(ID streamID) const {
    std::unordered_map<ID, Stream *> map = streamZ->getDatabase().getStreams();
    return map.find(streamID) != map.end();
}

bool SearchManager::adminExists() const {
    std::unordered_map<std::string, User *> userDB = streamZ->getDatabase().getUsers();

    return std::find_if(userDB.begin(),
                        userDB.end(),
                        [](const std::pair<std::string, User *> &pair) {
                            return pair.second->getUserType() == admin;
                        }) != userDB.end();
}

void SearchManager::listPrivateLiveStreams(std::vector<PrivateStream *> &streams) const {
    // Empties the vector if not empty
    if(!streams.empty()) streams.clear();

    // Iterator to the database map
    auto it1 = streamZ->getDatabase().getStreams().begin(),
            it2 = streamZ->getDatabase().getStreams().end();

    while(it1 != it2){
        Stream * ptr = (*it1).second; // Getting the current streamer pointer

        // Is a livestream?
        if(ptr->getStreamType() == privateType){
            streams.push_back(dynamic_cast<PrivateStream *>(ptr));
        }
        it1++;
    }

}

void SearchManager::listAllowedLiveStreams(std::vector<LiveStream *> &streams, std::string viewerNick,
                                           const std::string &streamName,
                                           const std::vector<genre> &genres, const std::vector<language> &langs) const{


    // Empties the vector if not empty
    if(!streams.empty()) streams.clear();


    bool checkGenres = !genres.empty(),
            checkLangs = !langs.empty();

    // Iterator to the database map
    auto it1 = streamZ->getDatabase().getStreams().begin(),
            it2 = streamZ->getDatabase().getStreams().end();

    // Loop to iterate over the map
    while(it1 != it2){
        Stream * ptr = (*it1).second; // Getting the current streamer pointer

        // Variable that identifies if the user is allowed to join the streamer or not
        bool valid = ptr->getStreamType() == publicType;

        if (!valid && ptr->getStreamType() == privateType){
            auto * privateStream = dynamic_cast<PrivateStream *>(ptr);
            valid = privateStream->isValidUser(viewerNick);
        }

        // Checks if the current streamer verifies all 3 requests (or those asked)
        if( valid &&
            (streamName.empty() || ptr->getTitle() == streamName) &&
            // Only verifies the vector if it is not empty (if the user wants to specify genre)
            (!checkGenres || checkParam<genre>(genres,ptr->getGenre())) &&
            // Only verifies the vector if it is not empty (if the user wants to specify genre)
            (!checkLangs || checkParam<language>(langs, ptr->getStreamLanguage())) )
        {
            streams.push_back(dynamic_cast<LiveStream *>((*it1).second));
        }

        it1++;
    }
}



