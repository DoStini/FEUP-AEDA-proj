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
class StreamZ;


class Stream {
public:
    /**
     * Constructor when creating a new stream
     *
     * @param title - Title of the stream
     * @param language - Stream language
     * @genre genre - genre of the stream
     * @param minAge - Minimal age of the stream , 12 by default
     */
    Stream(std::string title, language language, genre genre);
    ///@return - Title of the stream
    const std::string &getTitle() const;
    ///@return - stream language
    const language &getStreamLanguage() const;
    ///@return - date when the stream begin
    const Date &getBeginDate() const;
    ///@return - stream genre
    genre getGenre() const;
    ///@return - value that represent the stream id
    unsigned long long int getStreamId() const;
    /// @return - type of the stream
    virtual streamType getStreamType() const = 0;
    ///@param streamZ - pointer to the streamZ master class
    void setStreamZ(StreamZ *streamZ);

protected:
    /// General class that have all the info
    StreamZ * streamZ = nullptr;
    ///ID of the stream
    unsigned long long int streamID;
private:
    ///Stream title
    std::string title;
    ///Stream begin date
    Date beginDate;
    ///Stream language
    language streamLanguage;
    ///Stream genre
    genre streamGenre;

};


#endif //FEUP_AEDA_PROJ_STREAM_H
