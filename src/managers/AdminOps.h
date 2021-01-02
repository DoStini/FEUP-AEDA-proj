//
// Created by andremoreira9 on 28/10/20.
//

#ifndef FEUP_AEDA_PROJ_ADMINOPS_H
#define FEUP_AEDA_PROJ_ADMINOPS_H

#include <string>
#include <map>

#include "utils.h"
#include "Date.h"
#include "EmptyDatabaseException.h"

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
    /**
     * @throw EmptyDatabase if the custom search doesn't find anything
     * @return Pointer to the most viewed streamer
     */
    Streamer * mostViewed();
    /**
     * @param reversed - Optional: Set to true if you want the least viewed language
     * @throw EmptyDatabase if the custom search doesn't find anything
     * @return Most viewed language among streams ( enum language)
     */
    language rankViewsLang(bool reversed = false);
    /**
     * @param reversed - Optional: Set to true if you want the least viewed genre
     * @throw EmptyDatabase if the custom search doesn't find anything
     * @return Most viewed genre among streams ( enum genre)
     */
    genre rankViewsGenres(bool reversed = false);
    /**
     * @param reversed - Optional: Set to true if you want the least viewed genre
     * @throw EmptyDatabase if the custom search doesn't find anything
     * @return Most viewed genre among streams ( enum genre)
     */
    streamType rankViewsTypes(bool reversed = false);
    /// @return The median views per stream
    float medianViewsStream();

    float medianViewsStream(Date d1, Date d2);
    /// @return The number of all of the streams ever created
    long int numStreamsAll();

    /**
     * Returns the number of active (or inactive) streams in the system
     * @param activeStr - Option: Indicates if wants the count of active or inactive
     * @return
     */
    long int numStreams(bool activeStr = true);
    /**
     * @param streamType - The specific type (public, private or finished)
     * @return The number of streams of the specified type
     */
    long int numStreams(streamType streamType);
    /**
     * Number of streams between the specified dates
     * @param d1 - Smaller date
     * @param d2 - Bigger date
     * @return Number of streams
     */
    long int numStreams(Date d1, Date d2);
    /**
     * Number of streams between the specified dates of the specified type
     * @param streamType - The specific type (public, private or finished)
     * @param d1 - Smaller date
     * @param d2 - Bigger date
     * @return
     */
    long int numStreams(streamType streamType, Date d1, Date d2);

    /**
     * Removes a user
     * @throw DoesNotExist<std::string>
     * @param nickName Nickname of the user
     */
    void removeUser(std::string nickName);
    /**
     * Removes a streamer
     * @throw DoesNotExist<ID>
     * @param streamID ID of the streamer
     */
    void removeStream(ID streamID);

    /**
     * @brief changes the max size of orders each streamer can have
     * @param size the new max size
     */
    void changeMaxOrdersSize(size_t size);

    /**
     * @brief gets the max size of orders each streamer can have
     * @return the size
     */
    unsigned getMaxOrdersSize();

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_ADMINOPS_H
