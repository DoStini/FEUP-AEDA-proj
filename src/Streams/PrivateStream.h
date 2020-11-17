//
// Created by adbp on 18/10/2020.
//

#ifndef FEUP_AEDA_PROJ_PRIVATESTREAM_H
#define FEUP_AEDA_PROJ_PRIVATESTREAM_H

#include <utility>

#include "AlreadyInWhiteListException.h"
#include "NotInWhiteListException.h"
#include "MaxViewersReach.h"
#include "LiveStream.h"


// struct used to save comments in the streamer
struct Comment{
    std::string comment;
    std::string viewerNick;
    Comment(std::string text, std::string name): comment(std::move(text)),viewerNick(std::move(name)){}
    friend std::ostream &operator<<(std::ostream & out,const Comment& val){
        out << std::endl <<  val.viewerNick << "-> " << val.comment;
        return out;
    }

};

class PrivateStream : public LiveStream {
public:
    PrivateStream();
    /**
     * Constructor to private streamer
     *
     * @param title - Title of the streamer
     * @param language - Stream language
     * @param minAge - Minimal age of the streamer , 12 by default
     */
    PrivateStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick,
                  unsigned minAge = VIEWER_MIN_AGE, unsigned maxViewers = MAX_VIEWERS);

    ///@return - number of comments that the streamer have
    unsigned getNumberComments();

    ///@return - streamer type = private type
    streamType getStreamType() const override;

    /// @return - Used to store the stream in the file
    streamFileType getStreamFileType() const;

    /**
     * Function to add a user to a whitelisted streamer
     * @param userNick - nick of user to be added
     */
    void addValidUser(const std::string& userNick);

    /**
     * Function to remove a user from the streamer whitelist
     * @throw NotInStreamException
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
     * save a comment in the streamer
     *
     * @param text - text that the user write
     * @param viewer - viewer that make the comment
     */
    void addComment(const std::string & text, const std::string & userNick);

    ///@return - max numbers of viewers that may be in the streamer
    unsigned int getMaxViewers() const;

    /**
    * Add viewers to the streamer
    *
    * @param viewerNick - Nick name of the viewer
    */
    void addViewer(const std::string& viewerNick);
    /**
     * Writing streamer info to file
     * @param ff Current file streamer
     */
    void readFromFile(std::ifstream &ff) override;
    /**
     * Writing streamer info from file
     * @param ff Current file streamer
     */
    void writeToFile(std::ofstream &ff) override;
    /// @return - relevant info about streamer
    std::string getShorDescription() const override;

    /// @return - detailed info about streamer
    std::string getLongDescription() const override;

private:
    ///vector that have all the comments made for the streamer
    std::vector<Comment> comments;
    ///Valid nick names to enter de streamer
    std::vector<std::string> whitelist;
    ///Max number of viewers of the streamer
    unsigned int maxViewers;
};


#endif //FEUP_AEDA_PROJ_PRIVATESTREAM_H
