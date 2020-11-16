//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_SEARCHMANAGER_H
#define FEUP_AEDA_PROJ_SEARCHMANAGER_H

#include "User.h"
#include "Stream.h"
#include "PrivateStream.h"
#include "DoesNotExist.h"

class StreamZ;

class User;
class LiveStream;


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
    bool userExists(std::string nick) const;
    /**
     * @param streamID - The id of the stream
     * @return If a stream with that ID exists
     */
    bool streamExists(ID streamID) const;
    /// @return If an admin account was already created
    bool adminExists() const;
    /// @return Corresponding user to the nickname
    User * getUser(std::string userNick) const;
    /// @return Corresponding stream to the streamID
    Stream * getStream(ID streamID) const;
    /**
     * @param name - Name of user to be searched
     * @return Vector of users with the specified name
     */
    void listUsers(std::vector<User *> & users, const std::string& name = "") const;

    /**
     * Function that returns by param a vector of livestreams. Clears the vector passed if not empty
     * @param streams
     */
    //void listLiveStreams(std::vector<LiveStream *> & streams);
    /**
     * @param Returns by reference the vector of streams corresponding to the specified params - Will be cleared if not empty
     * @param streamName - Optional param specifying the name of the streams to search
     * @param genres - Optional param specifying the genre(s) of the streams to search
     * @param langs - Optional param specifying the language(s) of the streams to search
     */
    void listLiveStreams(std::vector<LiveStream *> & streams, const std::string& streamName = "",
                         unsigned minAge = VIEWER_MIN_AGE,
                         const std::vector<genre> & genres = std::vector<genre>(),
                         const std::vector<language> & langs = std::vector<language>()) const;

    void listPrivateLiveStreams(std::vector<PrivateStream *> & streams) const;
    /**
     * List live streams corresponding to some streamers
     * @param streams - Returns by reference the vector of livestreams from the streamers - Will be cleared if not empty
     * @param streamerID - Vector of streamer ID's
     */
    void listLiveStreamsByStreamers(std::vector<LiveStream *> & streams, const std::vector<std::string> & streamerNick) const;

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_SEARCHMANAGER_H

