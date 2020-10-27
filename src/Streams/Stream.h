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
#include <sstream>

#include "utils.h"
#include "Date.h"

class User;
class Viewer;


class Stream {
public:
    /**
     * Constructor when creating a new stream
     *
     * @param title - Title of the stream
     * @param language - Stream language
     * @param minAge - Minimal age of the stream , 12 by default
     */
    Stream(std::string title, std::string language,genres genre /*REMOVE, unsigned minAge = VIEWER_MIN_AGE*/);
    /**
     * Give the title of the stream
     *
     * @return
     */
    const std::string &getTitle() const;
    /**
     * Give us basic stream title, number of viewers, language and necessary age to join
     *
     * @return - string with all the info
     */
    virtual std::string getInfo() const = 0;
    /**
     * Give us the stream language
     *
     * @return - stream language
     */
    const std::string &getStreamLanguage() const;
    /**
     * add id to the stream
     *
     * @param streamId - lastID value
     */
    void setStreamId(unsigned long long int streamId);
    /**
     * Add viewers to the stream
     *
     * @param viewer - pointer to viewer
     */
    void addViewer(User * viewer); // TO REMOVE
    /**
     * Remove viewer from the stream
     *
     * @param viewer - viewer pointer
     */
    void removeViewer(User * viewer); // TO REMOVE
    /**
     * Give the number of viewers in the stream
     *
     * @return - number of viewers
     */
    unsigned getNumViewers() const; // TO REMOVE
    /**
     * Give us the stream min age
     *
     * @return - stream min age
     */
    unsigned getMinAge() const; // TO REMOVE
    /**
     * Function used to end stream
     *
     * @return - corrent number of viewers
     */
    unsigned closeStream(); // TO REMOVE
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
    genres genre;
    unsigned long long int streamId;
    unsigned minAge; // to remove
    std::vector<User *> streamViewers; // to remove

};


#endif //FEUP_AEDA_PROJ_STREAM_H
