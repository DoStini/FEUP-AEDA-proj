//
// Created by adbp on 18/10/2020.
//

#ifndef FEUP_AEDA_PROJ_PUBLICSTREAM_H
#define FEUP_AEDA_PROJ_PUBLICSTREAM_H

#include "LiveStream.h"

class PublicStream : public LiveStream {
public:

    /**
     * Constructor to Public Stream
     *
     * @param title - Title of the stream
     * @param language - Stream language
     * @param minAge - Minimal age of the stream , 12 by default
     */
    PublicStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick, unsigned minAge);

    ///@return - stream type = public type
    streamType getStreamType() const override;

    /**
    * Add viewers to the stream
    *
    * @param viewerNick - Nick name of the viewer
    */
    void addViewer(const std::string& viewerNick) override;

    /// @return - relevant info about stream
    std::string getShorDescription() const override;

    /// @return - detailed info about stream
    std::string getLongDescription() const override;
};


#endif //FEUP_AEDA_PROJ_PUBLICSTREAM_H
