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
#include <fstream>

#include "utils.h"
#include "Date.h"

class User;
class StreamZ;


class Stream {
public:
    Stream();
    /**
     * Constructor when creating a new stream
     *
     * @param title - Title of the stream
     * @param language - Stream language
     * @param genre - genre of the stream
     * @param minAge - Minimal age of the stream , 12 by default
     */
    Stream(std::string title, language language, genre genre, std::string streamerNick);

    virtual ~Stream(){};

    ///@return - Title of the stream
    const std::string &getTitle() const;

    ///@return - stream language
    const language &getStreamLanguage() const;

    ///@return - date when the stream begin
    const Date &getBeginDate() const;

    ///@return - stream genre
    genre getGenre() const;

    ///@return - value that represent the stream id
    ID getStreamId();

    /// @return - nick of the streamer
    const std::string &getStreamerNick() const;

    /// @return - type of the stream
    virtual streamType getStreamType() const = 0;

    /// @return - relevant info about stream
    virtual std::string getShorDescription() const = 0;

    /// @return - detailed info about stream
    virtual std::string getLongDescription() const = 0;

    /**
     * Set stream id to the given value
     * @param streamId - lastID value
     */
    void setStreamId(ID streamId);

    ///@param streamZ - pointer to the streamZ master class
    void setStreamZ(StreamZ *streamZ);

    /**
     * Function to read a User from the files
     * @param ifstream
     */
    virtual void readFromFile(std::ifstream & ff ) = 0;
    /**
     * Function to write a User to the files
     * @param ofstream
     */
    virtual void writeToFile(std::ofstream  & ff ) = 0;

protected:
    /// General class that have all the info
    StreamZ * streamZ = nullptr;
    ///ID of the stream
    ID streamId;
    ///Stream title
    std::string title;
    ///Stream begin date
    Date beginDate;
    ///Stream language
    language streamLanguage;
    ///Stream genre
    genre streamGenre;
    /// NickName of the stream streamer
    std::string streamerNick;

};


#endif //FEUP_AEDA_PROJ_STREAM_H
