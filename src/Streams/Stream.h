//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_STREAM_H
#define FEUP_AEDA_PROJ_STREAM_H

#include <string>
#include "Date.h"

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
     *
     * @param n
     */
    void addViewer(int n = 1);
    /**
     * Give the number of viewers in the stream
     *
     * @return - number of viewers
     */
    unsigned getNumViewers() const;
    /**
     * Function used to end stream
     *
     * @return - corrent number of viewers
     */
    unsigned closeStream();

private:
    std::string title;
    Date beginDate;
    std::string streamLanguage;
    unsigned minAge;
    unsigned viewersNumber;
    bool liveStream;

};


#endif //FEUP_AEDA_PROJ_STREAM_H
