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
    /**
    * Add viewers to the stream
    *
    * @param viewer - pointer to viewer
    */
    void addViewer(const std::string& viewerNick);
    /**
    * Remove viewer from the stream
    *
    * @param viewer - viewer pointer
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
    unsigned closeStream(); //TODO CHANGE IN DATABASE
    ///@return - number of likes of the stream
    int getLikes() const;
    ///@return - give number of dislikes of the stream
    int getDislikes() const;
    /**
    * add like to the stream
    *
    * @param viewer - viewer that give like
    */
    void giveLike(const std::string& viewerNick);
    /**
    * add dislike to the stream
    *
    * @param viewer - viewer that give dislike
    */
    void giveDislike(const std::string& viewerNick);
    /**
    * remove feedback from the stream either like or dislike
    *
    * @param viewer - viewer that remove feedback
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
private:
    /// Necessary age to se the stream
    unsigned minAge;
    /// Vector with nicks of viewers of the stream
    std::vector<std::string> streamViewers;
    /// Map with all the feedback of viewers that react to the stream key = userNick, value = givenFeedback
    std::map<std::string,feedback> likeSystem;
    /// Number of like and dislikes of the stream
    std::pair<unsigned,unsigned> nLikes_Dislikes;
    /// Id of the last stream created
    static unsigned long long int lastId ;
};


#endif //FEUP_AEDA_PROJ_LIVESTREAM_H
