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
    StreamManager(StreamZ *streamZ);

    /**
     * Function to create a public stream
     * @param name - Desired name of the new stream
     * @param streamLanguage - Stream language
     * @param streamGenre - Stream genre
     * @param minAge - Minimum age for a viewer to join
     */
    void createPublicStream(std::string name, language streamLanguage, genre streamGenre, unsigned minAge = VIEWER_MIN_AGE);
    /**
     * Function to create a public stream
     * @param name - Desired name of the new stream
     * @param streamLanguage - Stream language
     * @param streamGenre - Stream genre
     * @param minAge - Minimum age for a viewer to join
     */
    void createPrivateStream(std::string name, language streamLanguage, genre streamGenre, int maxUsers, unsigned minAge = VIEWER_MIN_AGE);

    /// @param streamID - Stream id of the stream to be removed
    void removeStream(ID streamID);

    void removeStreamByStreamer(std::string streamerNick);

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_STREAMMANAGER_H
