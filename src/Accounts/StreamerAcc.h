//
// Created by Nuno Alves on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_STREAMERACC_H
#define FEUP_AEDA_PROJ_STREAMERACC_H

#include "Streamer.h"
#include "Account.h"

class StreamerAcc : public Account {
private:
    Streamer * streamer;
public:
    void run() override;
    void startStream();
    void kickUserFromStream();
    void addUserToPrivate();
    void endStream();
    void checkNumViewers();
    void checkNumFollowers();
};


#endif //FEUP_AEDA_PROJ_STREAMERACC_H
