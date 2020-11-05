//
// Created by andremoreira9 on 26/10/20.
//

#include <PublicStream.h>
#include "StreamZ.h"
#include "LiveStream.h"


void StreamZ::init() {

    //readFromFile();
    LiveStream::lastId = NULL_STREAM;
    sortingManager = new SortingManager(this);
    searchManager = new SearchManager(this);
    userManager = new UserManager(this);
    streamManager = new StreamManager(this);
    adminOps = new AdminOps(this);
    leaderboard = new LeaderBoard(this);
    dataBase = Database();
}

void StreamZ::shutdown() {
    //backupData();
    delete sortingManager;
    delete searchManager;
    delete userManager;
    delete streamManager;
    delete leaderboard;
}

SortingManager *StreamZ::getSortM(){
    return sortingManager;
}

SearchManager *StreamZ::getSearchM(){
    return searchManager;
}

UserManager *StreamZ::getUserM(){
    return userManager;
}

void StreamZ::run() {
}

Database &StreamZ::getDatabase(){
    return dataBase;
}

StreamManager *StreamZ::getStreamManager(){
    return streamManager;
}

AdminOps *StreamZ::getAdminOps() const {
    return adminOps;
}
