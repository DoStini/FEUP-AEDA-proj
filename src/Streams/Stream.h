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
    /**
     * Give the title of the stream
     *
     * @return
     */
    const std::string &getTitle() const;

    /**
     * Give us the stream language
     *
     * @return - stream language
     */
    const languages &getStreamLanguage() const;
    /**
     * Get date when the stream begin
     *
     * @return - date when the stream begin
     */
    const Date &getBeginDate() const;
    /**
     * Get genre of the stream
     *
     * @return - value of the genre of the stream in the enum
     */
    genres getGenre() const;
    /**
     * Get stream id
     *
     * @return - value that represent the stream id
     */
    unsigned long long int getStreamId() const;
    /**
     * Give us basic stream title, number of viewers, language and necessary age to join
     *
     * @return - string with all the info
     */
    virtual std::string getInfo() const = 0;
    virtual streamType getStreamType() const = 0;
    /**
     * add id to the stream
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
