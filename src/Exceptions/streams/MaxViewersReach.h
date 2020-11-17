//
// Created by adbp on 01/11/2020.
//

#ifndef FEUP_AEDA_PROJ_MAXVIEWERSREACH_H
#define FEUP_AEDA_PROJ_MAXVIEWERSREACH_H

#include <exception>
#include <ostream>

#include "utils.h"

class MaxViewersReach : public std::exception{

public:
    /**
     * Constructor
     * @param stream - The streamer that is not private
     * @param maxViewers - max number of viewers of the streamer
     */
    MaxViewersReach(unsigned long long intstreamId, unsigned maxViewers);
    /**
     * Brief info about exception
     * @return
     */
    const char * what() const noexcept override;

    friend std::ostream &operator<<(std::ostream &os, const MaxViewersReach &exception);

private:
    unsigned long long int streamId;
    unsigned maxViewers;
};


#endif //FEUP_AEDA_PROJ_MAXVIEWERSREACH_H
