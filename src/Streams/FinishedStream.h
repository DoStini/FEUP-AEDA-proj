//
// Created by adbp on 26/10/2020.
//

#ifndef FEUP_AEDA_PROJ_FINISHEDSTREAM_H
#define FEUP_AEDA_PROJ_FINISHEDSTREAM_H

#include "Stream.h"
class FinishedStream : public Stream{
public:
    /**
     * Constructor for a finished stream
     *
     * @param title - Title of the stream
     * @param language - Stream language
     * @param numViewers - Number of viewers when the stream is closed
     * @param streamerName - Streamer that had stream the stream
     */
    FinishedStream(std::string title, language language,genre streamGenre, int numViewers, std::string streamerName);
    /**
     * get type of the stream
     *
     * @return - finished type
     */
    streamType getStreamType() const override;
    std::string getInfo() const override = 0;

private:
    Date finishedDate;
    int numViewers;
    std::string streamerName;
};


#endif //FEUP_AEDA_PROJ_FINISHEDSTREAM_H
