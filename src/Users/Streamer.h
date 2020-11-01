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
    * @param birthDate - Date of Birth
    */
    Streamer(std::string name, std::string nickName, const Date &birthDate);
    ///@return - user type = streamer
    userType getUserType() const override;
    /**
     * Add viewer to the followers vector
     * @param viewerNick - nick of the viewer
     */
    void addFollower(std::string viewerNick);
    /**
     * Remove viewer to the followers vector
     * @param viewerNick - nick of the viewer
     */
    void removeFollower(std::string viewerNick);
    ///@return - number of followers of the streamer
    unsigned int getNumFollowers() const;
    /// @return - If the streamer is currently streaming or not
    bool streaming();
    /// @return - ID of the current stream
    ID getStreamID();
    /**
     * Start streaming a public stream
     * @param title - Title of the stream
     * @param language - Stream language
     * @genre genre - Genre of the stream
     * @param minAge - Minimal age of the stream , 12 by default
     */
    void startPublicStream(std::string title, language streamLanguage, genre streamGenre, unsigned minAge);
    /**
     * Start streaming a private stream
     * @param title - Title of the stream
     * @param language - Stream language
     * @genre genre - Genre of the stream
     * @param minAge - Minimal age of the stream , 12 by default
     */
    void startPrivateStream(std::string title, language streamLanguage, genre streamGenre, unsigned minAge);
    ///@return - number of viewers in the stream
    unsigned int getNumViewers() const;
    /**
     * Remove user from the stream
     * @param viewerNick - nick of the viewer
     */
    void kickUser(std::string viewerNick); // REMOVE MAYBE
    /**
     * Add user from the stream
     * @param viewerNick - nick of the viewer
     */
    void addUser(std::string viewerNick);// REMOVE MAYBE
    ///Command to end the current streaming stream
    void closeStream();
    ///Compare two streamers
    bool operator == (const Streamer & str);
private:
    ///Age of the user
    static const unsigned minimumAge = STREAMER_MIN_AGE;
    ///Number of viewers that follow the streamer
    std::vector<std::string> followedBy;
    ///Stream that stream is streaming
    ID currStreaming = NULL_STREAM;
    ///Streams that the streamer have ended
    std::vector<unsigned long long int> finishedStreams;
};


#endif //FEUP_AEDA_PROJ_STREAMER_H
