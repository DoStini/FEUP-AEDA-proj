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

/**
 * Streams master class
 */
class Stream {
public:
    Stream();
    /**
     * Constructor when creating a new streamer
     *
     * @param title - Title of the streamer
     * @param language - Stream language
     * @param genre - genre of the streamer
     * @param minAge - Minimal age of the streamer , 12 by default
     */
    Stream(std::string title, language language, genre genre, std::string streamerNick);

    virtual ~Stream(){};

    ///@return - Title of the streamer
    const std::string &getTitle() const;

    ///@return - streamer language
    const language &getStreamLanguage() const;

    ///@return - date when the streamer begin
    const Date &getBeginDate() const;

    ///@return - streamer genre
    genre getGenre() const;

    ///@return - value that represent the streamer id
    ID getStreamId() const;



    /// @return - nick of the streamer
    const std::string &getStreamerNick() const;

    /// @return - type of the streamer
    virtual streamType getStreamType() const = 0;

    /// @return - State of the stream
    virtual streamState getStreamState() const = 0;

    /// @return - Used to store the stream in the file
    virtual streamFileType getStreamFileType() const = 0;

    /// @return - Number of viewers
    virtual unsigned int getNumViewers() const = 0;

    /// @return - relevant info about streamer
    virtual std::string getShortDescription() const = 0;

    /// @return - detailed info about streamer
    virtual std::string getLongDescription() const = 0;

    /**
     * Set streamer id to the given value
     * @param id - lastID value
     */
    void setStreamId(ID id);

    ///@param pStreamZ - pointer to the streamZ master class
    void setStreamZ(StreamZ *pStreamZ);

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
    ///ID of the streamer
    ID streamId;
    ///Stream title
    std::string title;
    ///Stream begin date
    Date beginDate;
    ///Stream language
    language streamLanguage;
    ///Stream genre
    genre streamGenre;
    /// NickName of the streamer streamer
    std::string streamerNick;

};


#endif //FEUP_AEDA_PROJ_STREAM_H
