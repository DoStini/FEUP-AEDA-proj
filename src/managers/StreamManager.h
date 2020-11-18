//
// Created by andremoreira9 on 30/10/20.
//

#ifndef FEUP_AEDA_PROJ_STREAMMANAGER_H
#define FEUP_AEDA_PROJ_STREAMMANAGER_H

#include <string>
#include "utils.h"
#include "PublicStream.h"
#include "PrivateStream.h"


class StreamZ;


/**
 * Class to manage streams, like creating and removing streams
 */
class StreamManager {
public:
    /**
     * Constructor. StreamZ needs to use to access the database and other methods
     * @param streamZ - Main class pointer
     */
    explicit StreamManager(StreamZ *streamZ);

    /**
     * Function to create a public streamer
     * @param name - Desired name of the new streamer
     * @param streamLanguage - Stream language
     * @param streamGenre - Stream genre
     * @param minAge - Minimum age for a viewer to join
     */
    ID createPublicStream(std::string name, std::string streamerNick, language streamLanguage, genre streamGenre, unsigned minAge = VIEWER_MIN_AGE) const;
    /**
     * Function to create a public streamer
     * @param name - Desired name of the new streamer
     * @param streamLanguage - Stream language
     * @param streamGenre - Stream genre
     * @param minAge - Minimum age for a viewer to join
     */
    ID createPrivateStream(std::string name, std::string streamerNick, language streamLanguage, genre streamGenre, int maxUsers, unsigned minAge = VIEWER_MIN_AGE) const;

    /**
     * Removes a streamer from the system
     * @throw DoestNotExist
     * @param streamID
     */
    void removeStream(ID streamID) const;
    /**
     * Used when deleting a viewers
     * @param nick
     */
    void removeViewerFromWhitelists(std::string nick) const;
    /**
     * Deletes all of the streams from a specified streamer from the database and from history of viewers
     * Used when deleting a streamer
     * @throw DoesNotExist
     * @param streamerNick
     */
    void removeStreamByStreamer(std::string streamerNick) const;

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_STREAMMANAGER_H
