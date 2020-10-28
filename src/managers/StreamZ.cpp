//
// Created by andremoreira9 on 26/10/20.
//

#include <PublicStream.h>
#include "StreamZ.h"



void StreamZ::init() {

    //readFromFile();

    sortingManager = new SortingManager(this);
    searchManager = new SearchManager(this);
    userManager = new UserManager;
    leaderboard = new LeaderBoard;
    dataBase = Database();
}

void StreamZ::shutdown() {
    //backupData();
    delete sortingManager;
    delete searchManager;
    delete userManager;
    delete leaderboard;
}

SortingManager *StreamZ::getSortM() {
    return sortingManager;
}

SearchManager *StreamZ::getSearchM() {
    return searchManager;
}

UserManager *StreamZ::getUserM() {
    return userManager;
}

void StreamZ::run() {
}

Database &StreamZ::getDatabase() {
    return dataBase;
}



