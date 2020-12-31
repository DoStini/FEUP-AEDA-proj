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
 * Admin class
 * Specific type of user that can see statistic about the streams that are/where streamed
 */
class Viewer : public User{
public:
    Viewer();
    /**
     * Constructor when creating a new user
     * @throw RestrictedAgeException if the user is not allowed to create an account
     * @throw RestrictedStreamException if the user is not whitelisted
     * @param name - Name of the user
     * @param nickName - Nickname
     * @param password - User password
     * @param birthDate - Date of Birth
     *
     * @throws RestrictedAgeException if the user is not allowed to create an account
     */
    Viewer(std::string name, std::string nickName,std::string password, const Date &birthDate);

    ~Viewer();

    ///@return - user type = viewer
    userType getUserType() const override;

    ///@return - ID of current watching streamer
    ID getCurrWatching() const;

    /// @return boolean indicating if the user is watching some streamer or not
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
     * Checks if the viewers is following a streamer
     * @param streamer - The streamer's nick
     * @return
     */
    bool isFollowing(std::string & streamer);

    /**
     * Join a streamer
     * @throw DoesNotExist
     * @throw AlreadyInStreamException
     * @throw RestrictedAgeExpeption
     * @throw RestrictedStreamExpeption
     * @param stream - Desired streamer
     */
    void joinStream(ID streamID);

    /** Leave the current streamer
     * @throw NotInStreamException
     */
    void leaveStream();

    /**
     * Function to be used only when deleting a streamer from the system deleting the streamer pointer
     */
    void kickedStream();

    /**
     * Add streamer to the streamer history
     *
     * @param streamID - streamer to be added to the history
     */
    void addStreamHistory(ID streamID);

    /**
     * Remove streamer from the streamer history
     *
     * @param streamID - streamer to be removed from the history
     */
    void removeStreamHistory(ID streamID);

    /**
     * Checks if a streamer is in the streamer history
     * @param streamID - id of the streamer to be checked
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
     * Leave a comment on the (private) streamer currently watching
     * @throw NotInStreamException
     * @throw NotPrivateStreamException
     * @param comment - The comment
     */
    void giveFeedBack(const std::string& comment);

    /**
     * Gets the stream history of viewer
     * @return stream history
     */
    const std::vector<ID> &getHistory() const;

    /**
     * Returns the streamers the user is following
     * @return following streamers
     */
    const std::vector<std::string> &getFollowingStreamers() const;
    /**
     * Reading user info from file
     * @param ff Current file streamer
     */
    void readFromFile(std::ifstream & ff ) override;
    /**
     * Writing user info to file
     * @param ff Current file streamer
     */
    void writeToFile(std::ofstream  & ff ) override;
    void orderMerch(const std::string& streamerNick, unsigned num, unsigned availability);
    MerchandisingOrder removeOrder(const std::string& streamerNick);

    /// Returns a short description with info about the user
    ///@return Short description
    std::string getShortDescription() const override;

    /// Returns a long description with info about the user
    ///@return Long description
    std::string getLongDescription(bool seePassword = false) const override;
    /// Info about the viewer's following streamers
    /// @return - string with all the following
    std::string getFollowDetails() const override;
    /// Info about the history of the viewer's past streams
    /// @return - string with all the streamer history
    std::string getHistoryDetails() const override;

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
