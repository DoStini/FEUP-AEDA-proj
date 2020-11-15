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
     * Function to create a public stream
     * @param name - Desired name of the new stream
     * @param streamLanguage - Stream language
     * @param streamGenre - Stream genre
     * @param minAge - Minimum age for a viewer to join
     */
    ID createPublicStream(std::string name, std::string streamerNick, language streamLanguage, genre streamGenre, unsigned minAge = VIEWER_MIN_AGE);
    /**
     * Function to create a public stream
     * @param name - Desired name of the new stream
     * @param streamLanguage - Stream language
     * @param streamGenre - Stream genre
     * @param minAge - Minimum age for a viewer to join
     */
    ID createPrivateStream(std::string name, std::string streamerNick, language streamLanguage, genre streamGenre, int maxUsers, unsigned minAge = VIEWER_MIN_AGE);

    /**
     * Removes a stream from the system
     * @throw DoestNotExist
     * @param streamID
     */
    void removeStream(ID streamID);
    void removeViewerFromWhitelists(std::string nick);
    /**
     * Deletes all of the streams from a specified streamer from the database and from history of viewers
     * @throw DoesNotExist
     * @param streamerNick
     */
    void removeStreamByStreamer(std::string streamerNick);

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_STREAMMANAGER_H
