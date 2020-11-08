//
// Created by andremoreira9 on 27/10/20.
//

#include "UserManager.h"
#include "Viewer.h"
#include "StreamZ.h"

UserManager::UserManager(StreamZ *streamZ) : streamZ(streamZ) {}

bool UserManager::userExists(std::string nickName) const{


    return true;
}

void UserManager::createViewer(std::string userName, std::string nickName, Date date, std::string password) const{
    Viewer * viewer = new Viewer(userName, nickName, date);
    viewer->changePassword(password);
    viewer->setReference(streamZ);
    streamZ->getDatabase().getUsers()[nickName] = viewer;
}

void UserManager::createStreamer(std::string userName, std::string nickName, Date date, std::string password) const{
    Streamer * streamer = new Streamer(userName, nickName, date);
    streamer->changePassword(password);
    streamer->setReference(streamZ);
    streamZ->getDatabase().getUsers()[nickName] = streamer;
}

void UserManager::changePassword(const std::string &basicString) const{

}

void UserManager::removeUser(std::string nickName) const{

}

void UserManager::createAdmin(std::string userName, std::string nickName, Date date, std::string password) const{
    Admin * admin = new Admin(userName, nickName, date);
    admin->changePassword(password);
    admin->setReference(streamZ);
    streamZ->getDatabase().getUsers()[nickName] = admin;
}
