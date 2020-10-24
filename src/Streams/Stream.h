//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_STREAM_H
#define FEUP_AEDA_PROJ_STREAM_H

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

#include "Date.h"

class User;
class Viewer;

enum feedback{
    like,
    dislike,
    none
};

class Stream {
public:
    /**
     * Constructor when creating a new stream
     *
     * @param title - Title of the stream
     * @param language - Stream language
     * @param minAge - Minimal age of the stream , 12 by default
     */
    Stream(std::string title, std::string language, unsigned minAge = 12);
    /**
     * Give the title of the stream
     *
     * @return
     */

    virtual std::string getInfo() const = 0;

    const std::string &getTitle() const;
    /// give number of likes of the stream
    int getLikes() const;
    /// give number of dislikes of the stream
    const int getDislikes() const;
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
    /**
     * Compare stream with there minAge
     *
     * @param compStream - stream to compare
     * @return - stream that is being compared
     */
    // Change this operator later
    bool operator<(Stream * compStream);

private:
    std::string title;
    Date beginDate;
    std::string streamLanguage;
    unsigned minAge;
    std::vector<User *> streamViewers;
    bool liveStream;
    std::map<std::string,feedback> likeSystem;
    std::pair<unsigned,unsigned> nLikes_Dislikes;
};


#endif //FEUP_AEDA_PROJ_STREAM_H
