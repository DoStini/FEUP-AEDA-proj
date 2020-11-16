//
// Created by andremoreira9 on 30/10/20.
//

#include "StreamManager.h"

#include <utility>
#include "StreamZ.h"

void StreamManager::removeStream(ID streamID) {
    if(!streamZ->getSearchM()->streamExists(streamID)) throw DoesNotExist<ID>(streamID);

    Stream * ptr = streamZ->getSearchM()->getStream(streamID);

    delete ptr;

    streamZ->getDatabase().getStreams().erase(streamID);

}

void StreamManager::removeStreamByStreamer(std::string streamerNick) {
    if(!streamZ->getSearchM()->userExists(streamerNick)) throw DoesNotExist<std::string>(streamerNick);
    std::unordered_map<ID, Stream *> mapRef = streamZ->getDatabase().getStreams();
    /*
    mapRef.erase(std::remove_if(
                    mapRef.begin(),
                    mapRef.end(),
                    [streamerNick](Stream * str){return str->getStreamer() == streamerNick;}),
                 mapRef.end());
    */
}

StreamManager::StreamManager(StreamZ *streamZ) : streamZ(streamZ) {}

ID StreamManager::createPublicStream(std::string name, std::string streamerNick, language streamLanguage,
                                     genre streamGenre, unsigned int minAge) {
    auto * ptr = new PublicStream(std::move(name), streamLanguage, streamGenre,std::move(streamerNick), minAge);
    ptr->setStreamZ(streamZ);
    streamZ->getDatabase().getStreams().insert(std::pair<ID, Stream *>(ptr->getStreamId(), (Stream *) ptr ));
    return ptr->getStreamId();
}

ID StreamManager::createPrivateStream(std::string name, std::string streamerNick, language streamLanguage,
                                      genre streamGenre, int maxUsers, unsigned int minAge) {
    auto * ptr = new PrivateStream(std::move(name), streamLanguage, streamGenre,std::move(streamerNick), minAge);
    ptr->setStreamZ(streamZ);
    streamZ->getDatabase().getStreams().insert(
            std::pair<ID, Stream *>(ptr->getStreamId(), dynamic_cast<Stream *>(ptr)));

    return ptr->getStreamId();
}

void StreamManager::removeViewerFromWhitelists(std::string nick) {
    auto it1 = streamZ->getDatabase().getStreams().begin(),
            ite = streamZ->getDatabase().getStreams().end();

    while(it1 != ite){
        if(it1->second->getStreamType() == privateType){
            PrivateStream * ptr = dynamic_cast<PrivateStream *>(it1->second);

            try {
                ptr->removeValidUser(nick);
            } catch (const std::exception & e) {
            }
        }
        it1++;
    }


}
