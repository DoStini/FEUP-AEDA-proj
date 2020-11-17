//
// Created by andremoreira9 on 26/10/20.
//

#ifndef FEUP_AEDA_PROJ_STREAMZ_H
#define FEUP_AEDA_PROJ_STREAMZ_H

#include <iostream>

#include "Database.h"
#include "SortingManager.h"
#include "SearchManager.h"
#include "AdminOps.h"
#include "UserManager.h"
#include "LeaderBoard.h"
#include "utils.h"
#include "Admin.h"
#include "StreamManager.h"

#include "User.h"
#include "Viewer.h"
#include "Streamer.h"
#include "AdminOps.h"

#include "Account.h"
#include "ViewerAcc.h"
#include "StreamerAcc.h"
#include "AdminAcc.h"





class StreamZ {
    SortingManager * sortingManager;
    SearchManager * searchManager;
    UserManager * userManager;
    StreamManager * streamManager;
    LeaderBoard * leaderboard;
    AdminOps * adminOps;
    Database dataBase;
public:
    void init();
    void shutdown(std::string fileName);
    /**
     * Runs the program and prompts the user to login/register/exit the program.
     */
    void run();
    /**
     * Asks the user to login and insert the correct credentials.
     */
    void login();
    /**
     * Asks the user to register.
     */
    void registerUser();

    void backupData(std::string fileName);
    void readFromFile(std::string fileName);
    void resetDatabase();
    const SortingManager * getSortM();
    const SearchManager * getSearchM();
    const UserManager * getUserM();
    const LeaderBoard * getLeaderBoard();
    const AdminOps * getAdminOps();
    Database & getDatabase();
};


#endif //FEUP_AEDA_PROJ_STREAMZ_H
