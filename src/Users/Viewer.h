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
     * @throw RestrictedAgeException if the user is not allowed to create an account
     * @throw RestrictedStreamException if the user is not whitelisted
     * @param name - Name of the user
     * @param nickName - Nickname
     * @param birthDate - Date of Birth
     */
    Viewer(std::string name, std::string nickName, const Date &birthDate);
    ~Viewer();
    ///@return - user type = viewer
    userType getUserType() const override;
    ///@return - ID of current watching stream
    ID getCurrWatching() const;
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
     * Removes a streamer from the vector
     * Used only by streamer destructor
     * @param streamer
     */
    void removeFollowStreamer(const std::string & streamer);
    /**
     * Checks if the viewers is following a streamer
     * @param streamer - The streamer's nick
     * @return
     */
    bool isFollowing(std::string & streamer);
    /**
     * Join a stream
     * @throw DoesNotExist
     * @throw AlreadyInStreamException
     * @throw RestrictedAgeExpeption
     * @throw RestrictedStreamExpeption
     * @param stream - Desired stream
     */
    void joinStream(ID streamID);
    /** Leave the current stream
     * @throw NotInStreamException
     */
    void leaveStream();
    /**
     * Function to be used only when deleting a stream from the system deleting the stream pointer
     */
    void kickedStream();
    /**
     * Add stream to the stream history
     *
     * @param streamID - stream to be added to the history
     */
    void addStreamHistory(ID streamID);
    void removeStreamHistory(ID streamID);
    /**
     * Checks if a stream is in the stream history
     * @param streamID - id of the stream to be checked
     * @return - true if it is, otherwise false
     */
    bool isInStreamHistory(ID streamID);
    /**
     * Gives feedback
     * @throw NotInStreamException
     * @param fbValue - Feedback value
     */
    void giveFeedBack(feedback fbValue);
    /**
     * Leave a comment on the (private) stream currently watching
     * @throw NotInStreamException
     * @throw NotPrivateStreamException
     * @param comment - The comment
     */
    void giveFeedBack(const std::string& comment);

private:
    /// Minimum age to be able to create a viewer account
    static const unsigned minimumAge = VIEWER_MIN_AGE;
    /// Stream currently watching
    ID currWatching = 0;
    /// List of streamers nicks the viewer follows
    std::vector<std::string> followingStreamers;
    /// Vector of streams that user have seen
    std::vector<ID> streamHistory;
};


#endif //FEUP_AEDA_PROJ_VIEWER_H
