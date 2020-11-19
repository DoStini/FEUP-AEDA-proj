//
// Created by adbp on 18/10/2020.
//

#ifndef FEUP_AEDA_PROJ_PUBLICSTREAM_H
#define FEUP_AEDA_PROJ_PUBLICSTREAM_H

#include "LiveStream.h"
#include <fstream>


/**
 *
 * PublicStream inherited from LiveStream to handle changes in publicStream elements
 */
class PublicStream : public LiveStream {
public:
    PublicStream();
    /**
     * Constructor to Public Stream
     *
     * @param title - Title of the streamer
     * @param language - Stream language
     * @param minAge - Minimal age of the streamer , 12 by default
     */
    PublicStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick, unsigned minAge);

    ///@return - streamer type = public type
    streamType getStreamType() const override;

    /// @return - Used to store the stream in the file
    streamFileType getStreamFileType() const override;

    /**
    * Add viewers to the streamer
    *
    * @param viewerNick - Nick name of the viewer
    */
    void addViewer(const std::string& viewerNick) override;
    /**
     * Reading streamer info to file
     * @param ff Current file streamer
     */
    void readFromFile(std::ifstream &ff) override;
    /**
     * Writing streamer info to file
     * @param ff Current file streamer
     */
    void writeToFile(std::ofstream &ff) override;
    /// @return - relevant info about streamer
    std::string getShortDescription() const override;

    /// @return - detailed info about streamer
    std::string getLongDescription() const override;
};


#endif //FEUP_AEDA_PROJ_PUBLICSTREAM_H
