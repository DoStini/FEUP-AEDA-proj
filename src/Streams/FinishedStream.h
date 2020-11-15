//
// Created by adbp on 26/10/2020.
//

#ifndef FEUP_AEDA_PROJ_FINISHEDSTREAM_H
#define FEUP_AEDA_PROJ_FINISHEDSTREAM_H

#include "Stream.h"
class FinishedStream : public Stream{
public:
    FinishedStream();
    /**
     * Constructor for a finished stream
     *
     * @param title - Title of the stream
     * @param language - Stream language
     * @param numViewers - Number of viewers when the stream is closed
     * @param streamerName - Streamer that had stream the stream
     */
    FinishedStream(std::string title, language language,genre streamGenre, int numViewers, std::string streamerNick, ID streamID);
    ~FinishedStream();
    /**
     * get type of the stream
     *
     * @return - finished type
     */
    streamType getStreamType() const override;

     /// @return - Date when the stream end
    const Date &getFinishedDate() const;

    int getNumViewers() const;

    /// @return - relevant info about stream
    std::string getShorDescription() const override;

    /// @return - detailed info about stream
    std::string getLongDescription() const override;

    void writeToFile(std::ofstream &ff) override;
    void readFromFile(std::ifstream &ff) override;

private:
    Date finishedDate;
    int numViewers;
};


#endif //FEUP_AEDA_PROJ_FINISHEDSTREAM_H
