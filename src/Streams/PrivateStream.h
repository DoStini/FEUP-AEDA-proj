//
// Created by adbp on 18/10/2020.
//

#ifndef FEUP_AEDA_PROJ_PRIVATESTREAM_H
#define FEUP_AEDA_PROJ_PRIVATESTREAM_H

#include "LiveStream.h"
class User;

// struct used to save comments in the stream
struct Comment{
    std::string comment;
    std::string viewerName;
    Comment(std::string text, std::string name): comment(text),viewerName(name){}
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
    PrivateStream(std::string title, language streamLanguage, genre streamGenre, unsigned minAge = VIEWER_MIN_AGE);

    std::string getInfo() const override;
    ///@return - number of comments that the stream have
    unsigned getNumberComments();
    ///@return - stream type = private type
    streamType getStreamType() const override;
    /**
     * Function to add a user to a whitelisted stream
     * @param user - User to be added
     */
    void addValidUser(User * user);
    /**
     * Checks if the user is in the vector of valid users
     *
     * @param user - user to check
     * @return - true if it is, otherwise false
     */
    bool isValidUser(User * user);
    /// @return Number of whitelisted viewers
    int getWhitelistSize() const;
    /**
     * save a comment in the stream
     *
     * @param text - text that the user write
     * @param viewer - viewer that make the comment
     */
    void addComment(std::string text, User * viewer);

private:
    std::vector<Comment> comments;
    std::vector<User *> whitelist;
};


#endif //FEUP_AEDA_PROJ_PRIVATESTREAM_H
