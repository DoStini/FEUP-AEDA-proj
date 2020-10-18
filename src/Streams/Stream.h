//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_STREAM_H
#define FEUP_AEDA_PROJ_STREAM_H

#include <string>
#include <vector>

#include "Date.h"
#include "User.h"



class Stream {
public:
    /**
     * Constructor when creating a new stream
     *
     * @param title - Title of the stream
     * @param language - Stream language
     * @param minAge - Minimal age of the stream , 13 by default
     */
    Stream(std::string title, std::string language, unsigned minAge = 13);
    /**
     * Add viewers to the stream
     * @param viewer - pointer to viewer
     */
    void addViewer(User * viewer); // must receive viewer and chek is age!!!
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
    /**
     * add like to the stream
     */
    void giveLike();
    /**
     * add dislike to the stream
     */
    void giveDislikes();
    /**
     * remove like from the stream
     */
    void removeLike();
    /**
     * remove dislike from the stream
     */
    void removeDislike();
    /**
     * Compare stream with there minAge
     *
     * @param compStream - stream to compare
     * @return - stream that is being compared
     */
    bool operator<(Stream * compStream);

private:
    std::string title;
    Date beginDate;
    std::string streamLanguage;
    unsigned minAge;
    std::vector<User *> streamViewers;
    bool liveStream;
    unsigned nLikes;
    unsigned nDislikes;
};


#endif //FEUP_AEDA_PROJ_STREAM_H
