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
    Stream(std::string title, languages language,genres genre /*REMOVE, unsigned minAge = VIEWER_MIN_AGE*/);
    ///@return - Title of the stream
    const std::string &getTitle() const;
    ///@return - stream language
    const languages &getStreamLanguage() const;
    ///@return - date when the stream begin
    const Date &getBeginDate() const;
    ///@return - stream genre
    genres getGenre() const;
    ///@return - value that represent the stream id
    unsigned long long int getStreamId() const;
    /**
     * Give us basic stream title, number of viewers, language and necessary age to join
     *
     * @return - string with all the info
     */
    virtual std::string getInfo() const = 0;
    /// @return - type of the stream
    virtual streamType getStreamType() const = 0;
    /**
     * Set stream id to the given value
     *
     * @param streamId - lastID value
     */
    void setStreamId(unsigned long long int streamId);

private:
    std::string title;
    Date beginDate;
    languages streamLanguage;
    genres genre;
    unsigned long long int streamId;

};


#endif //FEUP_AEDA_PROJ_STREAM_H
