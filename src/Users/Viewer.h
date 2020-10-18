//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_VIEWER_H
#define FEUP_AEDA_PROJ_VIEWER_H

#include "User.h"
#include "Stream.h"
#include "Streamer.h"

/**
 * Viewer class
 * Specific type of user that can watch streams and interact with them
 */
class Viewer : public User{
public:
    /**
     * Constructor when creating a new user
     * @param name - Name of the user
     * @param nickName - Nickename
     * @param birthDate - Date of Birth
     */
    Viewer(std::string name, std::string nickName, const Date &birthDate);
    /**
     * Info about the viewer
     * @return String containing info about the viewer
     */
    std::string getInfo() const;
    /**
     * Follow streamer
     * @param streamer - The desired streamer
     * @return Boolean value indicating if it's possible to follow the streamer or not
     */
    bool followStreamer(Streamer * streamer);

private:
    static const unsigned minimumAge = 12;
    /// Stream currently watching
    Stream * currWatching;
    /// List of streamers the viewer follows
    std::vector<Streamer *> followingStreamers;

};


#endif //FEUP_AEDA_PROJ_VIEWER_H
