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
    LiveStream();
    /**
     * Constructor of a LiveStream
     *
     * @param title - title of the streamer
     * @param language - language of the streamer
     * @param genre - genre of the streamer
     * @param minAge - min age of the streamer
     */
    LiveStream(std::string title, language streamLanguage, genre streamGenre, std::string streamerNick, unsigned minAge = VIEWER_MIN_AGE);
    ~LiveStream();

    /**
    * Add viewers to the streamer
    *
    * @param viewerNick - Nick name of the viewer
    */
    virtual void addViewer(const std::string& viewerNick) = 0 ;

    /**
    * Remove viewer from the streamer
    *
    * @param viewerNick - Nick name of the viewer
    */
    void removeViewer(const std::string& viewerNick);

    ///@return - number of viewers in the streamer
    int getNumViewers() const;

    ///@return - Stream min age
    unsigned getMinAge() const;

    ///@return - return type of the streamer
    streamType getStreamType() const override = 0;

    /// @return - State of the stream
    streamState getStreamState() const final;
    /**
    * Function used to end streamer
    *
    * @return - corrent number of viewers
    */
    unsigned closeStream();

    ///@return - number of likes of the streamer
    unsigned int getLikes() const;

    ///@return - give number of dislikes of the streamer
    unsigned int getDislikes() const;

    /**
    * add like to the streamer
    *
    * @param viewerNick - Nick name of the viewer
    */
    void giveLike(const std::string& viewerNick);

    /**
    * add dislike to the streamer
    *
    * @param viewerNick - Nick name of the viewer
    */
    void giveDislike(const std::string& viewerNick);

    /**
    * remove feedback from the streamer either like or dislike
    *
    * @param viewerNick - Nick name of the viewer
    */
    void removeFeedBack(const std::string& viewerNick);

    /**
    * Compare streamer with there minAge
    *
    * @param compStream - streamer to compare
    * @return - streamer that is being compared
    */
    // Change this operator later
    bool operator<(LiveStream * compStream);

    /// Static variable that stores the last id of the streamer ( Not allowing repeated id's )f
    static ID lastId ;
protected:

    /// Necessary age to se the streamer
    unsigned minAge;
    /// Vector with nicks of viewers of the streamer
    std::vector<std::string> streamViewers;
    /// Map with all the feedback of viewers that react to the streamer key = userNick, value = givenFeedback
    std::map<std::string,feedback> likeSystem;
    /// Number of like and dislikes of the streamer
    std::pair<unsigned,unsigned> nLikes_Dislikes;
    virtual void writeToFile(std::ofstream &ff) = 0;
    virtual void readFromFile(std::ifstream &ff) = 0;

};


#endif //FEUP_AEDA_PROJ_LIVESTREAM_H
