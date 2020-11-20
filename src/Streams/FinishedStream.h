//
// Created by adbp on 26/10/2020.
//

#ifndef FEUP_AEDA_PROJ_FINISHEDSTREAM_H
#define FEUP_AEDA_PROJ_FINISHEDSTREAM_H

#include "Stream.h"

/**
 *
 * PublicStream inherited from Stream to handle changes in finishStream elements
 */
class FinishedStream : public Stream{
public:
    FinishedStream();
    /**
     * Constructor for a finished streamer
     *
     * @param title - Title of the streamer
     * @param language - Stream language
     * @param numViewers - Number of viewers when the streamer is closed
     * @param streamerNick - Streamer nick that was streaming
     * @param streamID - The id of the stream
     * @param type - The type of the stream (public or private)
     */
    FinishedStream(std::string title, language language,genre streamGenre, int numViewers, std::string streamerNick,
                   ID streamID, streamType type);
    ~FinishedStream() override;

    /**
     * Get type of the streamer
     * @return - finished type
     */
    streamType getStreamType() const override;

    /// @return - State of the stream
    streamState getStreamState() const override;

     /// @return - Date when the streamer end
    const Date &getFinishedDate() const;

    /// @return - Used to store the stream in the file
    streamFileType getStreamFileType() const override;

    /// @return - Number of viewers when stream ended
    unsigned int getNumViewers() const;
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

    /// @return - relevant info about stream
    std::string getShortDescription() const override;

    /// @return - detailed info about stream
    std::string getLongDescription() const override;


private:
    Date finishedDate;
    int numViewers;
    streamType type;
};


#endif //FEUP_AEDA_PROJ_FINISHEDSTREAM_H
