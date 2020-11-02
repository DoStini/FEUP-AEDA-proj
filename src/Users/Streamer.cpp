//
// Created by andre on 10/18/2020.
//

#include "Streamer.h"
#include "StreamZ.h"


Streamer::Streamer(std::string name, std::string nickName, const Date &birthDate) :
        User(name, std::move(nickName), birthDate) {
    if(age <= minimumAge)
        throw RestrictedAgeException(name, age, minimumAge);

}

userType Streamer::getUserType() const {
    return stream;
}

bool Streamer::operator==(const Streamer &str) {
    return nickName == str.nickName;
}

bool Streamer::streaming() {
    return currStreaming != NULL_STREAM;
}

ID Streamer::getStreamID() {
    return currStreaming;
}

unsigned int Streamer::getNumViewers()  {

    unsigned int views;

    Stream * ptr = streamZ->getSearchM()->getStream(currStreaming);

    if(streaming()) views += dynamic_cast<LiveStream *>(ptr)->getNumViewers();

    for(const auto & id : finishedStreams){
        ptr = streamZ->getSearchM()->getStream(id);
        views += dynamic_cast<FinishedStream *>(ptr)->getNumViewers();
    }

    return views;

}
