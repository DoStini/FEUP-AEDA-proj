//
// Created by Nuno Alves on 02/11/2020.
//

#include "AdminOps.h"

AdminOps::AdminOps(StreamZ *streamZ) {
    this->streamZ = streamZ;
}

void AdminOps::removeUser(std::string nickName) const{

}

void AdminOps::removeStream(ID streamID) const{

}

Streamer *AdminOps::mostViewed() const {
    return nullptr;
}

language AdminOps::rankViewsLang(bool reversed) const {
    return SPA;
}

genre AdminOps::rankViewsGenres(bool reversed) const {
    return music;
}

streamType AdminOps::rankViewsTypes(bool reversed) const {
    return finishedType;
}

float AdminOps::medianViewsStream() const {
    return 0;
}

float AdminOps::medianViewsStream(Date d1, Date d2) const {
    return 0;
}

long int AdminOps::numStreamsAll() const {
    return 0;
}

long int AdminOps::numStreams() const {
    return 0;
}

long int AdminOps::numStreams(streamType streamType) const {
    return 0;
}

long int AdminOps::numStreams(Date d1, Date d2) const {
    return 0;
}

long int AdminOps::numStreams(streamType streamType, Date d1, Date d2) const {
    return 0;
}
