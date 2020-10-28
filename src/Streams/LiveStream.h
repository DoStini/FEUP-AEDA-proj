//
// Created by adbp on 25/10/2020.
//

#ifndef FEUP_AEDA_PROJ_LIVESTREAM_H
#define FEUP_AEDA_PROJ_LIVESTREAM_H

#include <vector>
#include <string>
#include "Stream.h"
#include "User.h"

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
    LiveStream(std::string title, languages language, genres genre,unsigned minAge = VIEWER_MIN_AGE);
    /**
    * Add viewers to the stream
    *
    * @param viewer - pointer to viewer
    */
    void addViewer(User * viewer);
    /**
    * Remove viewer from the stream
    *
    * @param viewer - viewer pointer
    */
    void removeViewer(User * viewer);
    ///@return - number of viewers in the stream
    unsigned getNumViewers() const;
    ///@return - Stream min age
    unsigned getMinAge() const;
    ///@return - return type of the stream
    virtual streamType getStreamType() const = 0;
    /**
    * Function used to end stream
    *
    * @return - corrent number of viewers
    */
    unsigned closeStream();
    ///@return - number of likes of the stream
    int getLikes() const;
    ///@return - give number of dislikes of the stream
    int getDislikes() const;
    /**
    * add like to the stream
    *
    * @param viewer - viewer that give like
    */
    void giveLike(User * viewer);
    /**
    * add dislike to the stream
    *
    * @param viewer - viewer that give dislike
    */
    void giveDislike(User * viewer);
    /**
    * remove feedback from the stream either like or dislike
    *
    * @param viewer - viewer that remove feedback
    */
    void removeFeedBack(User * viewer);
    /**
    * Compare stream with there minAge
    *
    * @param compStream - stream to compare
    * @return - stream that is being compared
    */
    // Change this operator later
    bool operator<(LiveStream * compStream);
private:
    unsigned minAge;
    std::vector<std::string> streamViewers;
    std::map<std::string,feedback> likeSystem;
    std::pair<unsigned,unsigned> nLikes_Dislikes;
    std::string streamerNick;
    static unsigned long long int lastId ;
};


#endif //FEUP_AEDA_PROJ_LIVESTREAM_H
