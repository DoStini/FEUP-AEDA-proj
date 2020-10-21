//
// Created by adbp on 18/10/2020.
//

#ifndef FEUP_AEDA_PROJ_PUBLICSTREAM_H
#define FEUP_AEDA_PROJ_PUBLICSTREAM_H

#include "Stream.h"

class PublicStream : public Stream {
public:
    PublicStream(std::string title, std::string language, unsigned minAge = 13);
    std::string getInfo() const override;
};


#endif //FEUP_AEDA_PROJ_PUBLICSTREAM_H
