//
// Created by andre on 10/18/2020.
//

#include "Streamer.h"
#include "OrdersEmptyException.h"
#include "OrdersFullException.h"
#include "NoSuchOrderException.h"
#include <utility>
#include "StreamZ.h"
#include <iomanip>
#include <iostream>


Streamer::Streamer(const std::string& name, std::string nickName,std::string password, const Date &birthDate) :
        User(name, std::move(nickName),std::move(password), birthDate) {
    if(age() <= minimumAge)
        throw RestrictedAgeException(name, (int) age(), minimumAge);
    status = 0;
    active = true;
}

Streamer::Streamer(const std::string & nick) : User(nick) {}

Streamer::~Streamer() {
    if(streaming()){
        closeStream();
        // This moves the stream to finished stream, so it doesnt have problems in recursive deletion
    }

    for(const auto & curr : finishedStreams){
        streamZ->getStreamManager()->removeStream(curr);
    }
    for(const auto & curr : followedBy){
        Viewer * ptr = (Viewer *) streamZ->getSearchM()->getUser(curr);
        ptr->unFollowStreamer(nickName);
    }
}

userType Streamer::getUserType() const {
    return streamer;
}

bool Streamer::operator==(const Streamer &str) {
    return nickName == str.nickName;
}

bool Streamer::streaming() const {
    return currStreaming != NULL_STREAM;
}

ID Streamer::getStreamID() {
    if (currStreaming == 0)
        throw NotInStreamException(nickName);
    else return currStreaming;
}

unsigned int Streamer::getTotalViews() {
    unsigned int views = 0;

    Stream *ptr;

    if (streaming()) {
        ptr = streamZ->getSearchM()->getStream(currStreaming);
        views += dynamic_cast<LiveStream *>(ptr)->getNumViewers();
    }
    for (const auto &id : finishedStreams) {
        ptr = streamZ->getSearchM()->getStream(id);
        views += dynamic_cast<FinishedStream *>(ptr)->getNumViewers();
    }

    return views;
}

unsigned int Streamer::getStreamViewers() {
    if(!streaming())
        throw NotInStreamException(nickName);

    auto ptr =(LiveStream *) streamZ->getSearchM()->getStream(currStreaming);
    return ptr->getNumViewers();
}


void Streamer::addFollower(std::string viewerNick) {
    followedBy.push_back(viewerNick);
}

void Streamer::leaveFollower(std::string viewerNick) {
    followedBy.erase(find(followedBy.begin(),followedBy.end(),viewerNick));
}

unsigned int Streamer::getNumFollowers() const {
    return followedBy.size();
}

void Streamer::closeStream() {
    if(!streaming()) throw NotInStreamException(nickName);
    finishedStreams.push_back(currStreaming);

    dynamic_cast<LiveStream *>(streamZ->getSearchM()->getStream(currStreaming))->closeStream();
    currStreaming = NULL_STREAM;
}

void Streamer::startPublicStream(std::string title, language streamLanguage, genre streamGenre, unsigned int minAge) {
    if(streaming()) throw AlreadyInStreamException(nickName, currStreaming);
    ID streamID = streamZ->getStreamManager()->createPublicStream(std::move(title), nickName, streamLanguage, streamGenre, minAge);

    if(status == 1){
        auto * str = dynamic_cast<LiveStream *>(streamZ->getSearchM()->getStream(streamID));
        str->addBonusLikes(50);
        status++;
    }

    currStreaming = streamID;
}

void Streamer::startPrivateStream(std::string title, language streamLanguage, genre streamGenre, unsigned int minAge,
                                  unsigned int maxNumberViewers) {
    if(streaming()) throw AlreadyInStreamException(nickName, currStreaming);

    ID streamID = streamZ->getStreamManager()->createPrivateStream(std::move(title), nickName, streamLanguage, streamGenre, minAge);
    if(status == 1){
        auto * str = dynamic_cast<LiveStream *>(streamZ->getSearchM()->getStream(streamID));
        str->addBonusLikes(50);
        status++;
    }

    currStreaming = streamID;
}

void Streamer::kickUser(std::string viewerNick) {
    if(!streaming())
        throw NotInStreamException(nickName);

    if(!streamZ->getSearchM()->viewerExists(viewerNick))
        throw DoesNotExist<std::string>(viewerNick);

    auto viewer = (Viewer*) streamZ->getSearchM()->getUser(viewerNick);
    if(viewer->getCurrWatching() == currStreaming)
        viewer->leaveStream();
}

void Streamer::kickedStream() {
    if(!streaming()) throw NotInStreamException(nickName);

    currStreaming = NULL_STREAM;
}

std::string Streamer::getShortDescription() const {
    std::stringstream  ss1, ss2;
    ss1 << "| nick: " << nickName;
    ss2 << std::setw(20) << std::left << name << std::setw(45) << std::left << ss1.str() << std::setw(12) << std::left <<  "| Streamer";
    return ss2.str();
}

void Streamer::removeStreamHistory(ID streamID) {
    finishedStreams.erase(std::find(finishedStreams.begin(), finishedStreams.end(), streamID));
}

bool Streamer::isInStreamHistory(ID streamID) {
    return !(find(finishedStreams.begin(),finishedStreams.end(),streamID) == finishedStreams.end());
}

std::string Streamer::getLongDescription(bool seePassword) const {
    std::stringstream  ss;
    ss << "My name is " << name << std::endl
       << "My nickname is " << nickName << std::endl
       << "I am a streamer" << std::endl
       << "My password is " << (seePassword ? password : "*****") << " hope you enjoy my account :)\n"
    << "I was born in " << birthDate.getStringDate() << " so i have " << age() << " years.\n"
    << "Joined StreamZ in: " << joinedPlatformDate.getStringDate() << std::endl
    << "Currently have " << getNumFollowers() << " followers.\n";
    if(currStreaming == NULL_STREAM){
        ss << "Right now I am not streaming.\n";
    }
    else{
        ss << "Right now I am streaming: "
        << streamZ->getSearchM()->getStream(currStreaming)->getShortDescription() << std::endl;
    }
    ss << "I have streamed a total of " << finishedStreams.size() << " streams.\n";
    return ss.str();
}

std::string Streamer::getFollowDetails() const {
    std::stringstream  ss;
    ss << "My followers are:\n";
    for(const auto & it : followedBy){
        ss << it << std::endl;
    }
    return ss.str();
}

std::string Streamer::getHistoryDetails() const {
    std::stringstream  ss;
    ss << "My finished streams are:\n";
    for(const auto & it : finishedStreams){
        ss << streamZ->getSearchM()->getStream(it)->getShortDescription() << std::endl;
    }
    return ss.str();
}


void Streamer::writeToFile(std::ofstream &ff) {
    int numNames = 0;
    std::string counter;
    std::stringstream temp(name);
    while (temp >> counter) numNames ++;


    ff << numNames << " , " << name << " , " << nickName << " , " << password << " , " << active << " , " << (int)status << " , "
       << birthDate.getStringDate() << " , " << joinedPlatformDate.getStringDateTime()
       << " , " << currStreaming << " , "
       << followedBy.size() << " , ";

    for(const auto & str : followedBy){
        ff << str << " , ";
    }

    ff << finishedStreams.size() << " , ";

    for(const auto & id : finishedStreams){
        ff << id << " , ";
    }
    ff << std::endl;
}

void Streamer::readFromFile(std::ifstream &ff) {
    int numNames;
    char sep;

    std::string temp;
    std::stringstream ss;

    ff >> numNames >> sep;

    for (int i = 0; i < numNames; ++i) {
        ff >> temp;
        ss << temp << " ";
    }

    name = ss.str();
    int st;
    ff >> sep >> nickName >> sep >> password >> sep >> active >> sep >> st >> sep;

    status = (char) st;

    ff >> temp;
    birthDate = Date(temp, true);
    ff >> sep;

    // Clearing the string streamer
    ss.str(std::string());

    ff >> temp; ss << temp << " "; // Building date and hour/minute
    ff >> temp; ss << temp; // Building date and hour/minute


    joinedPlatformDate = Date(ss.str(), true);

    int size;
    ID id;

    ff >> sep >> currStreaming >> sep >> size >> sep;

    for (int i = 0; i < size; ++i) {
        ff >> temp >> sep;
        followedBy.push_back(temp);
    }

    ff >> size >> sep;

    for (int i = 0; i < size; ++i) {
        ff >> id >> sep;
        finishedStreams.push_back(id);
    }
}

Streamer::Streamer() = default;

MerchandisingOrder Streamer::dispatchOrder() {
    if(orders.empty()) throw OrdersEmptyException();
    MerchandisingOrder merchandisingOrder = orders.top();
    orders.pop();

    return merchandisingOrder;
}

void Streamer::addOrder(const std::string &viewerNick, unsigned int num, unsigned int availability) {
    if(streamZ->getUserM()->getOrdersSize() == orders.size()) throw OrdersFullException();

    MerchandisingOrder merchandisingOrder(viewerNick, nickName, num, availability);
    orders.push(merchandisingOrder);
}

MerchandisingOrder Streamer::removeOrder(const std::string &viewerNick) {
    std::priority_queue<MerchandisingOrder> copy;
    MerchandisingOrder merchandisingOrder("","",0,0);
    bool found = false;

    if(orders.empty()) throw NoSuchOrderException(viewerNick);

    while(!orders.empty()) {
        merchandisingOrder = orders.top();
        orders.pop();
        if(merchandisingOrder.getViewerName() == viewerNick) {
            found = true;
            break;
        }
        copy.push(merchandisingOrder);
    }

    while(!copy.empty()) {
        orders.push(copy.top());
        copy.pop();
    }

    if(!found) throw NoSuchOrderException(viewerNick);

    return merchandisingOrder;
}

MerchandisingOrder Streamer::getOrder() {
    if(orders.empty()) throw OrdersEmptyException();

    return orders.top();
}

void Streamer::disableAccount() {
    if(streaming()){
        closeStream();
    }
    active = false;
}

void Streamer::reenableAccount() {
    active = true;
    // Should receive bonus likes next time he starts a stream
    if(status == 0)
        status ++;
}

bool Streamer::isActive() const {
    return active;
}

char Streamer::getStatus() const {
    return status;
}

void Streamer::writeOrders(ofstream &ff) {
    if(!orders.empty())  {
        ff << nickName << " : ";
    }

    while(!orders.empty()) {
        auto order = orders.top();
        ff << order.getViewerName() << " , " << order.getNumMerch() << " , " << order.getAvailability();
        orders.pop();

        if(orders.empty()) ff << " /" << std::endl;
        else ff << " ; ";
    }
}

bool MerchandisingOrder::operator<(const MerchandisingOrder &pci) const {
    if(pci.numMerch < numMerch) return true;
    else if(pci.numMerch == numMerch) {
        return(availability < pci.availability);
    }
    return false;
}

MerchandisingOrder::MerchandisingOrder(std::string userName, std::string streamerName, unsigned int num, unsigned int avail) :
        viewerName(std::move(userName)), streamerName(std::move(streamerName)), numMerch(num), availability(avail){
    if(availability > 5) availability = 5;
    else if(availability < 1) availability = 1;

}

bool MerchandisingOrder::operator==(const MerchandisingOrder& merchandisingOrder) const {
    return viewerName == merchandisingOrder.viewerName;
}

std::ostream &operator<<(std::ostream &os, const MerchandisingOrder &order) {
    os << "Order from viewer " << order.viewerName << " to streamer "<< order.streamerName << " with " << order.numMerch
       << " products and of availability of " << order.availability;
    return os;
}


