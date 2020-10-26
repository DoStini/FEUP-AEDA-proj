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
    LiveStream(std::string title, std::string language, /*genres genre,*/unsigned minAge = VIEWER_MIN_AGE);
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
    /**
    * Give the number of viewers in the stream
    *
    * @return - number of viewers
    */
    unsigned getNumViewers() const;
    /**
    * Give us the stream min age
    *
    * @return - stream min age
    */
    unsigned getMinAge() const;
    /**
    * Function used to end stream
    *
    * @return - corrent number of viewers
    */
    unsigned closeStream();
    /// give number of likes of the stream
    int getLikes() const;
    /// give number of dislikes of the stream
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
private:
    unsigned minAge;
    std::vector<std::string> streamViewers;
    std::map<std::string,feedback> likeSystem;
    std::pair<unsigned,unsigned> nLikes_Dislikes;
    std::string streamerNick;
};


#endif //FEUP_AEDA_PROJ_LIVESTREAM_H
