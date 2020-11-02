//
// Created by adbp on 18/10/2020.
//

#ifndef FEUP_AEDA_PROJ_PRIVATESTREAM_H
#define FEUP_AEDA_PROJ_PRIVATESTREAM_H

#include <utility>

#include "AlreadyInWhiteListException.h"
#include "LiveStream.h"
#include "MaxViewersReach.h"
class User;

// struct used to save comments in the stream
struct Comment{
    std::string comment;
    std::string viewerNick;
    Comment(std::string text, std::string name): comment(std::move(text)),viewerNick(std::move(name)){}
};

class PrivateStream : public LiveStream {
public:
    /**
     * Constructor to private stream
     *
     * @param title - Title of the stream
     * @param language - Stream language
     * @param minAge - Minimal age of the stream , 12 by default
     */
    PrivateStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick,
                  unsigned minAge = VIEWER_MIN_AGE, unsigned maxViewers = MAX_VIEWERS);
    ///@return - number of comments that the stream have
    unsigned getNumberComments();
    ///@return - stream type = private type
    streamType getStreamType() const override;
    /**
     * Function to add a user to a whitelisted stream
     * @param userNick - nick of user to be added
     */
    void addValidUser(const std::string& userNick);
    /**
     * Function to remove a user from the stream whitelist
     * @param userNick - nick of user to be removed
     */
    void removeValidUser(const std::string& userNick);
    /**
     * Checks if the user is in the vector of valid users
     *
     * @param userNick - nick of user to check
     * @return - true if it is, otherwise false
     */
    bool isValidUser(const std::string& userNick);
    /// @return Number of whitelisted viewers
    int getWhitelistSize() const;
    /**
     * save a comment in the stream
     *
     * @param text - text that the user write
     * @param viewer - viewer that make the comment
     */
    void addComment(const std::string & text, const std::string & userNick);
    ///@return - max numbers of viewers that may be in the stream
    unsigned int getMaxViewers() const;
    /**
    * Add viewers to the stream
    *
    * @param viewerNick - Nick name of the viewer
    */
    void addViewer(const std::string& viewerNick);

private:
    ///vector that have all the comments made for the stream
    std::vector<Comment> comments;
    ///Valid nick names to enter de stream
    std::vector<std::string> whitelist;
    ///Max number of viewers of the stream
    unsigned int maxViewers;
};


#endif //FEUP_AEDA_PROJ_PRIVATESTREAM_H
