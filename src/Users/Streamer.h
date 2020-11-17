//
// Created by andre on 10/18/2020.
//



#ifndef FEUP_AEDA_PROJ_STREAMER_H
#define FEUP_AEDA_PROJ_STREAMER_H

#include "User.h"

/**
 * Class Streamer
 * The class that contains information and methods related to the streamer
 */
class Streamer : public User {
public:

    /**
    * Constructor when creating a new user
    * Throws a RestrictedAgeException if the user is not allowed to create an account
    * @param name - Name of the user
    * @param nickName - Nickname
    * @param password - User password
    * @param birthDate - Date of Birth
    */
    Streamer(std::string name, std::string nickName,std::string password, const Date &birthDate);


    Streamer();

    ~Streamer() override;

    ///@return - user type = streamer
    userType getUserType() const override;

    /**
     * Add viewer to the followers vector
     * @param viewerNick - nick of the viewer
     */
    void addFollower(std::string viewerNick);

    /**
     * Remove viewer from the followers vector
     * @param viewerNick - nick of the viewer
     */
    void leaveFollower(std::string viewerNick);

    ///@return - number of followers of the streamer
    unsigned int getNumFollowers() const;

    /// @return - If the streamer is currently streaming or not
    bool streaming();

    /// @return - The current streamer, or 0 if none
    ID getStreamID();

    /// @return - relevant info about user

    /// @return - detailed info about user
    std::string getLongDescription() const override;

    /// @return - string with all the followers
    std::string getFollowDetails() const override;

    /// @return - string with all the streams finished
    std::string getHistoryDetails() const override;

    /**
     * Start streaming a public streamer
     * @throw AlreadyInStreamException
     * @param title - Title of the streamer
     * @param language - Stream language
     * @genre genre - Genre of the streamer
     * @param minAge - Minimal age of the streamer , 12 by default
     */
    void startPublicStream(std::string title, language streamLanguage, genre streamGenre, unsigned minAge = VIEWER_MIN_AGE);

    /**
     * Start streaming a private streamer
     * @throw AlreadyInStreamException
     * @param title - Title of the streamer
     * @param language - Stream language
     * @param genre - Genre of the streamer
     * @param minAge - Minimal age of the streamer , 12 by default
     * @param maxNumberViewers - max number of viewers that the streamer will have
     */
    void startPrivateStream(std::string title, language streamLanguage, genre streamGenre,
                            unsigned minAge = VIEWER_MIN_AGE, unsigned int maxNumberViewers = MAX_VIEWERS);


    ///@return - total number of views
    unsigned int getTotalViews();

    ///@return - number of viewers in the streamer
    unsigned int getStreamViewers();

    /**
     * Remove user from the streamer
     * @throw DoesNotExist
     * @param viewerNick - nick of the viewer
     */
    void kickUser(std::string viewerNick);

    /**
     * Command to end the current streaming streamer
     * NotInStreamException
     */
    void closeStream();

    /**
     * Function to be used only when deleting a streamer from the system deleting the streamer pointer
     */
    void kickedStream();
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

    ///Compare two streamers
    std::string getShorDescription() const override;
    bool operator == (const Streamer & str);

    /**
     * Writing user info to file
     * @param ff Current file streamer
     */
    void writeToFile(std::ofstream &ff) override;
    /**
     * Reading user info from file
     * @param ff Current file streamer
    */
    void readFromFile(std::ifstream &ff) override;
private:
    ///Age of the user
    static const unsigned minimumAge = STREAMER_MIN_AGE;
    ///Number of viewers that follow the streamer
    std::vector<std::string> followedBy;
    ///Stream that streamer is streaming
    ID currStreaming = NULL_STREAM;
    ///Streams that the streamer have ended
    std::vector<ID> finishedStreams;

};


#endif //FEUP_AEDA_PROJ_STREAMER_H
