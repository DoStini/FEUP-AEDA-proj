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
    * remove feedback from the stream
    *
    * @param viewer - viewer that remove feedback
    */
    void removeFeedBack(User * viewer);
private:
    unsigned minAge;
    std::vector<std::string> streamViewers;
    std::map<std::string,feedback> likeSystem;
    std::pair<unsigned,unsigned> nLikes_Dislikes;
    std::string streamNick;
};


#endif //FEUP_AEDA_PROJ_LIVESTREAM_H
