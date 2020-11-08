//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_VIEWER_H
#define FEUP_AEDA_PROJ_VIEWER_H

#include "User.h"
#include "Streamer.h"
#include "Stream.h"
#include "LiveStream.h"
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
     * @param nickName - Nickename
     * @param birthDate - Date of Birth
     *
     * @throws RestrictedAgeException if the user is not allowed to create an account
     */
    Viewer(std::string name, std::string nickName, const Date &birthDate);
    /**
     * Info about the viewer
     * @return UserType containing info about the viewer
     */
    userType getUserType() const override;
    /// @return boolean indicating if the user is watching some stream or not
    bool watching();
    /**
     * Follow a streamer
     * @param streamer - The desired streamer
     */
    void followStreamer(std::string streamer);
    /**
     * Unfollow a streamer
     * @param streamer - Desired streamer
     */
    void unFollowStreamer(std::string streamer);
    /**
     * Join a stream
     * Might throw AlreadyInStreamException
     * @param stream - Desired stream
     *
     * @throws DoesNotExist if live stream with stream id does not exist.
     * @throws AlreadyInStreamException if user is already in a stream.
     * @throws RestrictedAgeException if user is not old enough.
     * @throws RestrictedStreamException if user is not allowed to join the stream.
     */
    void joinStream(ID streamID);
    /// Leave the current stream. @throws NotInStreamException if user is not in a stream.
    void leaveStream();
    /// Like the current stream
    void giveFeedBack(feedback fbValue);
    /**
     * Leave a comment on the (private) stream currently watching
     * @param comment - The comment
     */
    void giveFeedBack(std::string comment);

    const std::vector<ID> &getHistory() const;

    const std::vector<std::string> &getFollowingStreamers() const;

    unsigned long long int getStreamID() const;

    /// @return - relevant info about user
    std::string getShortDescription() const override;

    /// @return - detailed info about user
    std::string getLongDescription() const override;


private:
    /// Minimum age to be able to create a viewer account
    static const unsigned minimumAge = VIEWER_MIN_AGE;
    /// Stream currently watching
    Stream * currWatching = nullptr;
    /// List of streamers the viewer follows
    std::vector<std::string> followingStreamers;
    /// Vector of streams that user have seen
    std::vector<ID> streamHistory;
};


#endif //FEUP_AEDA_PROJ_VIEWER_H
