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
    PublicStream(std::string title, std::string language, genres genre, unsigned minAge);
    std::string getInfo() const override;
};


#endif //FEUP_AEDA_PROJ_PUBLICSTREAM_H
