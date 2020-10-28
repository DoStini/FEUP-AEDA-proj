//
// Created by andremoreira9 on 28/10/20.
//

#ifndef FEUP_AEDA_PROJ_ADMINOPS_H
#define FEUP_AEDA_PROJ_ADMINOPS_H

#include <string>
#include "utils.h"

class StreamZ;
class Streamer;

/**
 * Class to execute admin methods
 */
class AdminOps {
public:
    /**
     * Constructor. StreamZ needs to be used by the class to access the database and other methods
     * @param streamZ - Main class pointer
     */
    AdminOps(StreamZ *streamZ);
    /// @return Pointer to the most viewed streamer
    Streamer * mostViewed();
    /// @return Most common language among streams ( enum language)
    language mostCommonLang();
    /// @return Most common genre among streams ( enum genre)
    genre mostCommonGenre();
    /// @return The median views per stream
    float medianViewsStream();
    /// @return The number of active streams
    long int numStreams();
    /**
     * Removes a user
     * @param nickName Nickname of the user
     */
    void removeUser(std::string nickName);
    /**
     * Removes a stream
     * @param streamID ID of the stream
     */
    void removeStream(ID streamID);

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_ADMINOPS_H
