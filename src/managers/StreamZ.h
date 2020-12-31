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
#include "DonationManager.h"

#include "User.h"
#include "Viewer.h"
#include "Streamer.h"
#include "AdminOps.h"

#include "Account.h"
#include "ViewerAcc.h"
#include "StreamerAcc.h"
#include "AdminAcc.h"

/**
 *
 * StreamZ general class of all program used to link all the parts
 */
class StreamZ {
private:
    DonationManager * donationManager;
    SortingManager * sortingManager;
    SearchManager * searchManager;
    UserManager * userManager;
    StreamManager * streamManager;
    LeaderBoard * leaderboard;
    AdminOps * adminOps;
    Database dataBase;
public:
    /**
     * Initialize with clean data
     * Used for testing
     */
    void init();
    /**
     * Initialize the program with a specified database file path
     * @param fileName
     */
    void init(std::string fileName);
    /**
     * Shutdown the system and save the data
     * @param fileName
     */
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
    /**
     * Asks user to recover a streamer account
     */
    void recoverAccount();
    /**
     * Backup data to file
     * File will be stored as users_fileName and streams_fileName
     * @param fileName - Name of the database file name
     */
    void backupData(std::string fileName);
    /**
     * Read data from file
     * Files will be read as users_fileName and streams_fileName
     * @param fileName - Name of the database file name
     */
    void readFromFile(std::string fileName);
    /**
     * Clean the database
     */
    void resetDatabase();
    /// @return Pointer to active the sorting manager
    SortingManager * getSortM();
    /// @return Pointer to active the sorting manager
    SearchManager * getSearchM();
    /// @return Pointer to active the user manager
    UserManager * getUserM();
    /// @return Pointer to active the leaderboard
    LeaderBoard * getLeaderBoard();
    /// @return Pointer to active the admin operations manager
    AdminOps * getAdminOps();
    /// @return Pointer to active the stream manager
    StreamManager * getStreamManager();
    /// @return Reference to the database manager
    Database & getDatabase();

    DonationManager *getDonationManager() const;
};


#endif //FEUP_AEDA_PROJ_STREAMZ_H
