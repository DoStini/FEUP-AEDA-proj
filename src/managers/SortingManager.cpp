//
// Created by andremoreira9 on 27/10/20.
//

#include <algorithm>
#include "SortingManager.h"
#include "StreamZ.h"


SortingManager::SortingManager(StreamZ *streamZ) : streamZ(streamZ) {}

void SortingManager::sortStreamByViews(std::vector<LiveStream *> &streams, bool reversed) const {
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

void SortingManager::sortStreamByLikes(std::vector<LiveStream *> &streams, bool reversed) const{
    // If the streams vector is empty it gets the currently stored in the system
    // Otherwise it sorts the vector sent
    if(streams.empty()) streamZ->getSearchM()->listLiveStreams(streams);

    std::sort(streams.begin(),
              streams.end(),
              [reversed](LiveStream * ptr1, LiveStream * ptr2){
                    int v1 = (int)ptr1->getLikes() - (int)ptr1->getDislikes(),
                        v2 = (int)ptr2->getLikes() - (int)ptr2->getDislikes();
                    if(v1 > v2) return !reversed;
                    else if(v1 < v2) return reversed;
                    else return !reversed
                                    ? (int)ptr1->getLikes() > (int)ptr2->getLikes()
                                    : (int)ptr1->getLikes() < (int)ptr2->getLikes();
                                // In case of tie, appears the on with more likes first
              });
}


void SortingManager::sortStreamByDate(std::vector<LiveStream *> &streams, bool reversed) const {
    // If the streams vector is empty it gets the currently stored in the system
    // Otherwise it sorts the vector sent
    if(streams.empty()) streamZ->getSearchM()->listLiveStreams(streams);

    std::sort(streams.begin(),
              streams.end(),
              [reversed](LiveStream * ptr1, LiveStream * ptr2){
                  return !reversed
                         ? ( ptr1->getBeginDate() < ptr2->getBeginDate() )
                         : ( ptr1->getBeginDate() > ptr2->getBeginDate()  );
              });
}


void SortingManager::sortUserDatePlatform(std::vector<User *> &users, bool reversed) const{
    // If the users vector is empty it gets the currently stored in the system
    // Otherwise it sorts the vector sent
    if(users.empty()) streamZ->getSearchM()->listUsers(users);

    std::sort(users.begin(),
              users.end(),
              [reversed](User * ptr1, User * ptr2){
                  return !reversed
                         ? ( ptr1->getJoinedPlatformDate() > ptr2->getJoinedPlatformDate() )
                         : ( ptr1->getJoinedPlatformDate() < ptr2->getJoinedPlatformDate()  );
              });
}

void SortingManager::sortStreamByComments(std::vector<PrivateStream *> &streams, bool reversed) const{
    // If the streams vector is empty it gets the currently stored in the system
    // Otherwise it sorts the vector sent
    if(streams.empty()) streamZ->getSearchM()->listPrivateLiveStreams(streams);

    std::sort(streams.begin(),
              streams.end(),
              [reversed](PrivateStream * ptr1, PrivateStream * ptr2){
                  return !reversed
                         ? ( ptr1->getNumberComments() < ptr2->getNumberComments())
                         : ( ptr1->getNumberComments() > ptr2->getNumberComments());
              });
}
