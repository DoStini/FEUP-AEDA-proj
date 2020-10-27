//
// Created by andremoreira9 on 26/10/20.
//

#include "StreamZ.h"

void StreamZ::init() {

    //readFromFile();

    sortingManager = new SortingManager;
    searchManager = new SearchManager;
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



