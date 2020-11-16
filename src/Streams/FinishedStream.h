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
     * Constructor for a finished streamer
     *
     * @param title - Title of the streamer
     * @param language - Stream language
     * @param numViewers - Number of viewers when the streamer is closed
     * @param streamerName - Streamer that had streamer the streamer
     */
    FinishedStream(std::string title, language language,genre streamGenre, int numViewers, std::string streamerNick, ID streamID);
    ~FinishedStream();
    /**
     * get type of the streamer
     *
     * @return - finished type
     */
    streamType getStreamType() const override;

     /// @return - Date when the streamer end
    const Date &getFinishedDate() const;

    int getNumViewers() const;

    /// @return - relevant info about streamer
    std::string getShorDescription() const override;

    /// @return - detailed info about streamer
    std::string getLongDescription() const override;
    /**
     * Writing streamer info to file
     * @param ff Current file streamer
     */
    void writeToFile(std::ofstream &ff) override;
    /**
     * Reading streamer info from file
     * @param ff Current file streamer
     */
    void readFromFile(std::ifstream &ff) override;

private:
    Date finishedDate;
    int numViewers;
};


#endif //FEUP_AEDA_PROJ_FINISHEDSTREAM_H
