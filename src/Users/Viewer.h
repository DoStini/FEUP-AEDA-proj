//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_VIEWER_H
#define FEUP_AEDA_PROJ_VIEWER_H

#include "User.h"
#include "Streamer.h"
#include "PrivateStream.h"
#include "NotPrivateStreamException.h"


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
     * @param nickName - Nickname
     * @param birthDate - Date of Birth
     */
    Viewer(std::string name, std::string nickName, const Date &birthDate);
    ///@return - user type = viewer
    userType getUserType() const override;
    /// @return boolean indicating if the user is watching some stream or not
    bool watching() const;
    /**
     * Follow a streamer
     * @param streamer - The desired streamer
     */
    void followStreamer(const std::string& streamer);
    /**
     * Unfollow a streamer
     * @param streamer - Desired streamer
     */
    void unFollowStreamer(const std::string& streamer);
    /**
     * Join a stream
     * Might throw AlreadyInStreamException
     * @param stream - Desired stream
     */
    void joinStream(unsigned long long int streamID);
    /// Leave the current stream. Might throw a NotInStreamException
    void leaveStream();
    /// Add stream to the history of streams
    void addStreamHistory(unsigned long long int streamID);
    /// Like the current stream
    void giveFeedBack(feedback fbValue);
    /**
     * Leave a comment on the (private) stream currently watching
     * @param comment - The comment
     */
    void giveFeedBack(std::string comment);
private:
    /// Minimum age to be able to create a viewer account
    static const unsigned minimumAge = VIEWER_MIN_AGE;
    /// Stream currently watching
    unsigned long long int currWatching = 0;
    /// List of streamers nicks the viewer follows
    std::vector<std::string> followingStreamers;
    /// Vector of streams that user have seen
    std::vector<unsigned long long int> streamHistory;
};


#endif //FEUP_AEDA_PROJ_VIEWER_H
