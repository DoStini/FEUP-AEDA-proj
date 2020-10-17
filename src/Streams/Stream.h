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

private:
    std::string title;
    Date beginDate;
    std::string streamLanguage;
    unsigned minAge;
    unsigned viewersNumber;
    bool liveStream;

};


#endif //FEUP_AEDA_PROJ_STREAM_H
