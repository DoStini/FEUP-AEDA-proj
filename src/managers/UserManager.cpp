//
// Created by andremoreira9 on 27/10/20.
//

#include "UserManager.h"
#include "Viewer.h"
#include "NoSuchOrderException.h"
#include "StreamZ.h"

UserManager::UserManager(StreamZ *streamZ) : streamZ(streamZ), maxOrdersSize(10){}

void UserManager::createViewer(const std::string& name, std::string nickName,const std::string& password, const Date &birthDate) const {
    if(streamZ->getSearchM()->userExists(nickName)) throw AlreadyExists<std::string>(nickName);

    std::transform(nickName.begin(), nickName.end(), nickName.begin(), ::tolower);

    Viewer * ptr = new Viewer(name, nickName,password, birthDate);
    ptr->setStreamZ(streamZ);


    streamZ->getDatabase().getUsers().insert(std::pair<std::string, User*>(nickName,dynamic_cast<User *>(ptr)));
}

void UserManager::createStreamer(std::string name, std::string nickName,const std::string& password, const Date &birthDate) const {
    if(streamZ->getSearchM()->userExists(nickName)) throw AlreadyExists<std::string>(nickName);

    Streamer * ptr = new Streamer(name, nickName,password, birthDate);
    ptr->setStreamZ(streamZ);

    streamZ->getDatabase().getStreamers().insert(ptr);
}

void UserManager::createAdmin(std::string name, std::string nickName,const std::string& password, const Date &birthDate) const {
    if(streamZ->getSearchM()->adminExists()) throw AlreadyExists<std::string>("Admin");
    else if(streamZ->getSearchM()->userExists(nickName)) throw AlreadyExists<std::string>(nickName);

    Admin * ptr = new Admin(name, nickName,password, birthDate);
    ptr->setStreamZ(streamZ);


    streamZ->getDatabase().getUsers().insert(std::pair<std::string, User*>(nickName,dynamic_cast<User *>(ptr)));
}

void UserManager::removeUser(std::string nickName,  bool permanent) const{
    if(!streamZ->getSearchM()->userExists(nickName)) throw DoesNotExist<std::string>(nickName);

    User * ptr = streamZ->getSearchM()->getUser(nickName);

    if(ptr->getUserType() != streamer)
        streamZ->getDatabase().getUsers().erase(nickName);
    else{
        if(permanent){
            streamZ->getDatabase().getStreamers().erase(ptr);
            streamZ->getDonationManager()->deleteAllDonationsByNick(nickName);
            delete ptr;
        }
    }
}

void UserManager::removeHistoryElemFromUser(ID id) const {
    if(!streamZ->getSearchM()->streamExists(id)) throw DoesNotExist<ID>(id);

    auto & ref = streamZ->getDatabase().getUsers();

    for(auto & user : ref){
        User * ptr = user.second;
        if(ptr->getUserType() == viewer){
            auto * viewer = dynamic_cast<Viewer*>(user.second);
            if(viewer->isInStreamHistory(id)) viewer->removeStreamHistory(id);
        }
    }

    // TODO - NO LONGER EFFICIENT!!!
    for (User * ptr : streamZ->getDatabase().getStreamers()){
        auto * streamer = dynamic_cast<Streamer*>(ptr);
        if(streamer->isInStreamHistory(id)) streamer->removeStreamHistory(id);
    }
}

void UserManager::setOrdersSize(size_t size) {
    maxOrdersSize = size;
}

size_t UserManager::getOrdersSize() const {
    return maxOrdersSize;
}

void UserManager::removeMerchFromStreamers(const std::string viewerNick) const {
    auto it1 = streamZ->getDatabase().getUsers().begin(),
    it2 = streamZ->getDatabase().getUsers().end();
    Streamer * streamer;

    while(it1 != it2) {
        if(it1->second->getUserType() == userType::streamer) {
            streamer = reinterpret_cast<Streamer *>(it1->second);

            try {
                while(true) {
                    streamer->removeOrder(viewerNick);
                }
            } catch (NoSuchOrderException & ex) {

            }
        }

        it1++;
    }
}
