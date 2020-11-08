//
// Created by andremoreira9 on 27/10/20.
//

#include "UserManager.h"
#include "StreamZ.h"

UserManager::UserManager(StreamZ *streamZ) : streamZ(streamZ) {}

void UserManager::createViewer(const std::string& name, std::string nickName, const Date &birthDate) {
    if(streamZ->getSearchM()->userExists(nickName)) throw AlreadyExists<std::string>(nickName);

    std::transform(nickName.begin(), nickName.end(), nickName.begin(), ::tolower);

    Viewer * ptr = new Viewer(name, nickName, birthDate);
    ptr->setStreamZ(streamZ);

    // TODO PASSWORD
    ptr->changePassword(" temporario");

    streamZ->getDatabase().getUsers().insert(std::pair<std::string, User*>(nickName,dynamic_cast<User *>(ptr)));
}

void UserManager::createStreamer(std::string name, std::string nickName, const Date &birthDate) {
    if(streamZ->getSearchM()->userExists(nickName)) throw AlreadyExists<std::string>(nickName);

    Streamer * ptr = new Streamer(name, nickName, birthDate);
    ptr->setStreamZ(streamZ);

    // TODO PASSWORD
    ptr->changePassword(" temporario");

    streamZ->getDatabase().getUsers().insert(std::pair<std::string, User*>(nickName,dynamic_cast<User *>(ptr)));
}

void UserManager::createAdmin(std::string name, std::string nickName, const Date &birthDate) {
    if(streamZ->getSearchM()->adminExists()) throw AlreadyExists<std::string>("Admin");
    else if(streamZ->getSearchM()->userExists(nickName)) throw AlreadyExists<std::string>(nickName);

    Viewer * ptr = new Viewer(name, nickName, birthDate);
    ptr->setStreamZ(streamZ);

    // TODO PASSWORD
    ptr->changePassword(" temporario");

    streamZ->getDatabase().getUsers().insert(std::pair<std::string, User*>(nickName,dynamic_cast<User *>(ptr)));
}

void UserManager::removeUser(std::string nickName) {
    if(!streamZ->getSearchM()->userExists(nickName)) throw DoesNotExist<std::string>(nickName);

    User * ptr = streamZ->getSearchM()->getUser(nickName);

    streamZ->getDatabase().getUsers().erase(nickName);

    delete ptr;
}
