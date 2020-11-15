//
// Created by andremoreira9 on 26/10/20.
//

#include <PublicStream.h>
#include "StreamZ.h"
#include "LiveStream.h"


void StreamZ::init() {
    LiveStream::lastId = NULL_STREAM;
    sortingManager = new SortingManager(this);
    searchManager = new SearchManager(this);
    userManager = new UserManager(this);
    streamManager = new StreamManager(this);
    adminOps = new AdminOps(this);
    leaderboard = new LeaderBoard(this);
    dataBase = Database();
}

void StreamZ::shutdown(std::string fileName) {
    backupData(fileName);
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

    // Just some testing, remove later

    try {
        readFromFile("DB.txt");
    } catch (std::string e) {
        std::cout << e << std::endl;
    }
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

void StreamZ::backupData(std::string fileName) {

    std::ofstream ff("users_" + fileName, std::ofstream::trunc);

    // TODO EXCEPTION
    if (!ff.is_open()) throw "No file";

    for (const auto & userPair : getDatabase().getUsers()){
        ff << userPair.second->getUserType() << " : ";
        userPair.second->writeToFile(ff);
    }
    ff.close();


    ff.open("streams_" + fileName, std::ofstream::trunc);
    // TODO EXCEPTION
    if (!ff.is_open()) throw "No file";

    ff << LiveStream::lastId << std::endl;

    for (const auto & strPair : getDatabase().getStreams()){
        ff << strPair.second->getStreamType() << " : ";
        strPair.second->writeToFile(ff);
    }
    ff.close();

}

void StreamZ::readFromFile(std::string fileName) {
    std::ifstream ff;
    ff.open("users_" + fileName);

    //usersRef.clear();

    // TODO EXCEPTION
    if (!ff.is_open()) throw std::string("No file");


    int uType;
    char sep;
    while (ff.peek() != EOF){

        ff >> uType >> sep;

        if(ff.eof()) break;

        User * newUser;

        switch ((userType) uType ) {

            case viewer:
                newUser = new Viewer();
                break;
            case stream:
                newUser = new Streamer();
                break;
            case admin:
                newUser = new Admin();
                break;
        }

        newUser->readFromFile(ff);
        newUser->setStreamZ(this);
        dataBase.getUsers().insert(std::pair<std::string, User *>( newUser->getNickName(), newUser ));
    }

    ff.close();

    ff.open("streams_" + fileName);

    //usersRef.clear();

    // TODO EXCEPTION
    if (!ff.is_open()) throw std::string("No file");

    ff >> LiveStream::lastId;

    int sType;
    ID biggestID;


    while (ff.peek() != EOF){

        ff >> sType >> sep;

        if(ff.eof()) break;

        Stream * newStream;

        switch ((streamType) sType ) {

            case finishedType:
                newStream = new FinishedStream();
                break;
            case publicType:
                newStream = new PublicStream();
                break;
            case privateType:
                newStream = new PrivateStream();
                break;
        }

        newStream->readFromFile(ff);
        newStream->setStreamZ(this);
        dataBase.getStreams().insert(std::pair<ID, Stream *>( newStream->getStreamId(), newStream ));
    }

    ff.close();
}

void StreamZ::resetDatabase() {



}