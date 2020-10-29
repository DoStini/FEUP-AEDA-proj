//
// Created by andremoreira9 on 27/10/20.
//

#include "UserManager.h"
#include "Viewer.h"
#include "StreamZ.h"

UserManager::UserManager(StreamZ *streamZ) : streamZ(streamZ) {}

bool UserManager::userExists(std::string nickName) {


    return true;
}

void UserManager::createViewer(std::string userName, std::string nickName, Date date) {
    Viewer * viewer = new Viewer(userName, nickName, date);
    viewer->changePassword("123");
    streamZ->getDatabase().getUsers()[nickName] = viewer;
}

void UserManager::createStreamer(std::string userName, std::string nickName, Date date) {

}
