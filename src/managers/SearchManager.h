//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_SEARCHMANAGER_H
#define FEUP_AEDA_PROJ_SEARCHMANAGER_H

#include "User.h"
#include "Stream.h"
#include "PrivateStream.h"
#include "../Exceptions/DoesNotExist.h"

class StreamZ;

class User;
class LiveStream;

/**
 * Template function to check if a certain element is present in the vector
 * @tparam T - Type of data
 * @param vec - Vector of T elements
 * @param toFind - Value to check
 * @return If toFind is in the vector
 */
template <class T>
bool checkParam(const std::vector<T> & vec, T toFind){
    return std::find_if(vec.begin(),
                     vec.end(),
                     [toFind](T currVal){
                        return currVal == toFind;
                     }) != vec.end();
}


/**
 * Class to execute search methods over the database
 */
class SearchManager {
public:
    /**
     * Constructor. StreamZ needs to be used by the class to access the database and other methods
     * @param streamZ - Main class pointer
     */
    SearchManager(StreamZ *streamZ);
    /**
     * @param nick - Nickname of the user
     * @return If a user with that nickname exists
     */
    bool userExists(std::string nick);
    /**
     * @param streamID - The id of the stream
     * @return If a stream with that ID exists
     */
    bool streamExists(ID streamID);
    /// @return If an admin account was already created
    bool adminExists();
    /// @return Corresponding user to the nickname
    User * getUser(std::string userNick);
    /// @return Corresponding stream to the streamID
    Stream * getStream(ID streamID);
    /**
     * @param name - Name of user to be searched
     * @return Vector of users with the specified name
     */
    void listUsers(std::vector<User *> & users, const std::string& name = "");

    /**
     * Function to list all streams the viewer is allowed to watch
     * @param streams - Returns by reference the vector of streams corresponding to the specified params - Will be cleared if not empty
     * @param streamName - Optional param specifying the name of the streams to search
     * @param genres - Optional param specifying the genre(s) of the streams to search
     * @param langs - Optional param specifying the language(s) of the streams to search
     */
    void listAllowedLiveStreams(std::vector<LiveStream *> & streams, std::string viewerNick,  const std::string& streamName = "",
                                const std::vector<genre> & genres = std::vector<genre>(),
                                const std::vector<language> & langs = std::vector<language>());
    /**
     * @param Returns by reference the vector of streams corresponding to the specified params - Will be cleared if not empty
     * @param streamName - Optional param specifying the name of the streams to search
     * @param genres - Optional param specifying the genre(s) of the streams to search
     * @param langs - Optional param specifying the language(s) of the streams to search
     */
    void listLiveStreams(std::vector<LiveStream *> & streams, const std::string& streamName = "",
                                          const std::vector<genre> & genres = std::vector<genre>(),
                                          const std::vector<language> & langs = std::vector<language>());

    void listPrivateLiveStreams(std::vector<PrivateStream *> & streams);
    /**
     * List live streams corresponding to some streamers
     * @param streams - Returns by reference the vector of livestreams from the streamers - Will be cleared if not empty
     * @param streamerID - Vector of streamer ID's
     */
    void listLiveStreamsByStreamers(std::vector<LiveStream *> & streams, const std::vector<std::string> & streamerNick);

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_SEARCHMANAGER_H
