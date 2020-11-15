//
// Created by andremoreira9 on 26/10/20.
//

#ifndef FEUP_AEDA_PROJ_STREAMZ_H
#define FEUP_AEDA_PROJ_STREAMZ_H

#include <iostream>

#include "Database.h"
#include "SortingManager.h"
#include "SearchManager.h"
#include "UserManager.h"
#include "LeaderBoard.h"
#include "StreamManager.h"

#include "User.h"
#include "Viewer.h"
#include "Streamer.h"
#include "AdminOps.h"

class StreamZ {
    SortingManager * sortingManager;
    SearchManager * searchManager;
    UserManager * userManager;
    StreamManager * streamManager;
    LeaderBoard * leaderboard;
    AdminOps * adminOps;
public:
    AdminOps *getAdminOps() const;

private:
    Database dataBase;
public:
    void init();
    void shutdown(std::string fileName);
    void run();

    void backupData(std::string fileName);
    void readFromFile(std::string fileName);
    void resetDatabase();


    SortingManager * getSortM();
    SearchManager * getSearchM();
    UserManager * getUserM();
    StreamManager *getStreamManager();
    Database & getDatabase();
};


#endif //FEUP_AEDA_PROJ_STREAMZ_H
