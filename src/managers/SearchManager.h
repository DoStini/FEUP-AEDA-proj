//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_SEARCHMANAGER_H
#define FEUP_AEDA_PROJ_SEARCHMANAGER_H

#include "User.h"
#include "Stream.h"
#include "DoesNotExist.h"
#include "Viewer.h"

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

    /// @return Corresponding user to the nickname
    User * getUser(std::string userNick);
    /// @return Corresponding stream to the streamID
    Stream * getStream(long long int streamID);
    /// @returns Vector of all the users
    std::vector<User *> listUsers();

    /**
     * @param name - Name of user to be searched
     * @return Vector of users with the specified name
     */
    std::vector<User *> listUsers(std::string name);

     ///@return Vector of all the live streams
    std::vector<LiveStream *> listStreams();
    /**
     * @param streamName - Optional param specifying the name of the streams to search
     * @param genres - Optional param specifying the genre(s) of the streams to search
     * @param langs - Optional param specifying the language(s) of the streams to search
     * @return Vector of streams corresponding to the specified params
     */
    std::vector<LiveStream *> listStreams(std::string streamName = "",
                                          std::vector<genre> genres = std::vector<genre>(),
                                          std::vector<language> langs = std::vector<language>());
    /// @return Vector of live streams from a specified streamer
    std::vector<LiveStream *> listStreamsByStreamer(long long int streamerID);

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_SEARCHMANAGER_H
