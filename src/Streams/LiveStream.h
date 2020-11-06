//
// Created by adbp on 25/10/2020.
//

#ifndef FEUP_AEDA_PROJ_LIVESTREAM_H
#define FEUP_AEDA_PROJ_LIVESTREAM_H

#include <vector>
#include <string>
#include "Stream.h"
#include "User.h"
#include "FinishedStream.h"

enum feedback{
    like,
    dislike,
    none
};

class LiveStream : public Stream {
public:
    /**
     * Constructor of a LiveStream
     *
     * @param title - title of the stream
     * @param language - language of the stream
     * @param genre - genre of the stream
     * @param minAge - min age of the stream
     */
    LiveStream(std::string title, language streamLanguage, genre streamGenre, std::string streamerNick, unsigned minAge = VIEWER_MIN_AGE);
    ~LiveStream();

    /**
    * Add viewers to the stream
    *
    * @param viewerNick - Nick name of the viewer
    */
    virtual void addViewer(const std::string& viewerNick) = 0 ;

    /**
    * Remove viewer from the stream
    *
    * @param viewerNick - Nick name of the viewer
    */
    void removeViewer(const std::string& viewerNick);

    ///@return - number of viewers in the stream
    unsigned getNumViewers() const;

    ///@return - Stream min age
    unsigned getMinAge() const;

    ///@return - return type of the stream
    streamType getStreamType() const override = 0;

    /**
    * Function used to end stream
    *
    * @return - corrent number of viewers
    */
    unsigned closeStream();

    ///@return - number of likes of the stream
    unsigned int getLikes() const;

    ///@return - give number of dislikes of the stream
    unsigned int getDislikes() const;

    /**
    * add like to the stream
    *
    * @param viewerNick - Nick name of the viewer
    */
    void giveLike(const std::string& viewerNick);

    /**
    * add dislike to the stream
    *
    * @param viewerNick - Nick name of the viewer
    */
    void giveDislike(const std::string& viewerNick);

    /**
    * remove feedback from the stream either like or dislike
    *
    * @param viewerNick - Nick name of the viewer
    */
    void removeFeedBack(const std::string& viewerNick);

    /**
    * Compare stream with there minAge
    *
    * @param compStream - stream to compare
    * @return - stream that is being compared
    */
    // Change this operator later
    bool operator<(LiveStream * compStream);

    /// Static variable that stores the last id of the stream ( Not allowing repeated id's )f
    static ID lastId ;
protected:

    /// Necessary age to se the stream
    unsigned minAge;
    /// Vector with nicks of viewers of the stream
    std::vector<std::string> streamViewers;
    /// Map with all the feedback of viewers that react to the stream key = userNick, value = givenFeedback
    std::map<std::string,feedback> likeSystem;
    /// Number of like and dislikes of the stream
    std::pair<unsigned,unsigned> nLikes_Dislikes;

};


#endif //FEUP_AEDA_PROJ_LIVESTREAM_H
