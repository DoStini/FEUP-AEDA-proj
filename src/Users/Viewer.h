//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_VIEWER_H
#define FEUP_AEDA_PROJ_VIEWER_H

#include "User.h"
#include "Streamer.h"
#include "Stream.h"


/**
 * Viewer class
 * Specific type of user that can watch streams and interact with them
 */
class Viewer : public User{
public:
    /**
     * Constructor when creating a new user
     * Throws a RestrictedAgeException if the user is not allowed to create an account
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
     */
    void followStreamer(Streamer * streamer);
    /**
     * Unfollow a streamer
     * @param streamer - Desired streamer
     */
    void unFollowStreamer(Streamer * streamer);
    /**
     * Join a stream
     *
     * @param stream - Desired stream
     */
    void joinStream(Stream * stream);
    /**
     * Leave the current stream.
     *
     */
    void leaveStream();

private:
    static const unsigned minimumAge = 12;
    /// Stream currently watching
    Stream * currWatching = nullptr;
    /// List of streamers the viewer follows
    std::vector<Streamer *> followingStreamers;

};


#endif //FEUP_AEDA_PROJ_VIEWER_H
