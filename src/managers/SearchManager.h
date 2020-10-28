//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_SEARCHMANAGER_H
#define FEUP_AEDA_PROJ_SEARCHMANAGER_H

#include "User.h"
#include "Stream.h"
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
     * Constructor. StreamZ needs to use to access the database and other methods
     * @param streamZ - Main class pointer
     */
    SearchManager(StreamZ *streamZ);

    /// @return Corresponding user to the nickname
    User * getUser(std::string userNick);
    /// @return Corresponding stream to the streamID
    Stream * getStream(long long int streamID);

    std::vector<User *> listUsers();
    std::vector<User *> listUsers(std::string name);
    std::vector<LiveStream *> listStreams();
    std::vector<LiveStream *> listStreams(std::string streamName = "",
                                          std::vector<genre> genres = std::vector<genre>(),
                                          std::vector<language> langs = std::vector<language>());
    std::vector<LiveStream *> listStreamsByStreamer(long long int streamerID);

private:
    StreamZ * streamZ;

};


#endif //FEUP_AEDA_PROJ_SEARCHMANAGER_H
