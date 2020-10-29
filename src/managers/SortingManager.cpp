//
// Created by andremoreira9 on 27/10/20.
//

#include <algorithm>
#include "SortingManager.h"
#include "StreamZ.h"


SortingManager::SortingManager(StreamZ *streamZ) : streamZ(streamZ) {}

void SortingManager::sortStreamByViews(std::vector<LiveStream *> &streams, bool reversed) {
    // If the streams vector is empty it gets the currently stored in the system
    // Otherwise it sorts the vector sent
    if(streams.empty()) streamZ->getSearchM()->listLiveStreams(streams);

    std::sort(streams.begin(),
              streams.end(),
              [reversed](LiveStream * ptr1, LiveStream * ptr2){
                            return !reversed
                                ? ( ptr1->getNumViewers() > ptr2->getNumViewers() )
                                : ( ptr1->getNumViewers() < ptr2->getNumViewers() );
                        });

}

void SortingManager::sortStreamByLikes(std::vector<LiveStream *> &streams, bool reversed) {
    // If the streams vector is empty it gets the currently stored in the system
    // Otherwise it sorts the vector sent
    if(streams.empty()) streamZ->getSearchM()->listLiveStreams(streams);

    std::sort(streams.begin(),
              streams.end(),
              [reversed](LiveStream * ptr1, LiveStream * ptr2){
                  return !reversed
                         ? ( ptr1->getLikes() - ptr1->getDislikes() > ptr2->getLikes() - ptr2->getDislikes() )
                         : ( ptr1->getLikes() - ptr1->getDislikes() < ptr2->getLikes() - ptr2->getDislikes() );
              });
}


void SortingManager::sortStreamByDate(std::vector<LiveStream *> &streams, bool reversed) {
    // If the streams vector is empty it gets the currently stored in the system
    // Otherwise it sorts the vector sent
    if(streams.empty()) streamZ->getSearchM()->listLiveStreams(streams);

    std::sort(streams.begin(),
              streams.end(),
              [reversed](LiveStream * ptr1, LiveStream * ptr2){
                  return !reversed
                         ? ( ptr1->getBeginDate() > ptr2->getBeginDate() )
                         : ( ptr1->getBeginDate() < ptr2->getBeginDate()  );
              });
}

/*
void SortingManager::sortUserDatePlatform(std::vector<User *> &users, bool reversed) {
    // If the users vector is empty it gets the currently stored in the system
    // Otherwise it sorts the vector sent
    if(users.empty()) streamZ->getSearchM()->listLiveusers(users);

    std::sort(users.begin(),
              users.end(),
              [reversed](LiveStream * ptr1, LiveStream * ptr2){
                  return !reversed
                         ? ( ptr1->getBeginDate() > ptr2->getBeginDate() )
                         : ( ptr1->getBeginDate() < ptr2->getBeginDate()  );
              });
}
*/

