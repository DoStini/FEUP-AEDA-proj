//
// Created by adbp on 18/10/2020.
//

#ifndef FEUP_AEDA_PROJ_PRIVATESTREAM_H
#define FEUP_AEDA_PROJ_PRIVATESTREAM_H

#include <utility>

#include "LiveStream.h"
class User;

// struct used to save comments in the stream
struct Comment{
    std::string comment;
    std::string viewerName;
    Comment(std::string text, std::string name): comment(std::move(text)),viewerName(std::move(name)){}
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
    PrivateStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick, unsigned minAge);
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

private:
    std::vector<Comment> comments;
    std::vector<std::string> whitelist;
};


#endif //FEUP_AEDA_PROJ_PRIVATESTREAM_H
