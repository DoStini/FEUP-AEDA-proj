//
// Created by andremoreira9 on 28/10/20.
//

#ifndef FEUP_AEDA_PROJ_ADMINOPS_H
#define FEUP_AEDA_PROJ_ADMINOPS_H

#include <string>
#include <map>

#include "utils.h"
#include "Date.h"

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
    /**
     * @param reversed - Optional: Set to true if you want the least viewed language
     * @return Most viewed language among streams ( enum language)
     */
    language rankViewsLang(bool reversed = false) const;
    /**
     * @param reversed - Optional: Set to true if you want the least viewed genre
     * @return Most viewed genre among streams ( enum genre)
     */
    genre rankViewsGenres(bool reversed = false) const;
    /// @return The median views per stream
    float medianViewsStream() const;

    float medianViewsStream(Date d1, Date d2) const;
    /// @return The number of all of the streams ever created
    long int numStreamsAll() const;
    /// @return The number of active streams
    long int numStreams() const;
    /**
     * @param streamType - The specific type (public, private or finished)
     * @return The number of streams of the specified type
     */
    long int numStreams(streamType streamType) const;
    /**
     * Removes a user
     * @param nickName Nickname of the user
     */
    void removeUser(std::string nickName) const;
    /**
     * Removes a stream
     * @param streamID ID of the stream
     */
    void removeStream(ID streamID) const;

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_ADMINOPS_H
