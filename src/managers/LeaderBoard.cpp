//
// Created by andremoreira9 on 27/10/20.
//

#include "LeaderBoard.h"
#include "StreamZ.h"

LeaderBoard::LeaderBoard(StreamZ *streamZ) : streamZ(streamZ) {}

void LeaderBoard::top10StreamViews(std::vector<LiveStream *> &streams) {

    // Sort with specific genres or languages
    if(streams.empty()) streamZ->getSearchM()->listLiveStreams(streams);

    streamZ->getSortM()->sortStreamByViews(streams);

    // If the vector contains more than 10 entries
    if (streams.size() > 10)
        streams.erase(streams.begin() + 10, streams.end());
}

void LeaderBoard::top10StreamLikes(std::vector<LiveStream *> &streams) {
    // Sort with specific genres or languages
    if(streams.empty()) streamZ->getSearchM()->listLiveStreams(streams);

    streamZ->getSortM()->sortStreamByViews(streams);

    // If the vector contains more than 10 entries
    if (streams.size() > 10)
        streams.erase(streams.begin() + 10, streams.end());
}

void LeaderBoard::top10StreamComments(std::vector<PrivateStream *> &streams) {
    // Sort with specific genres or languages
    if(streams.empty()) streamZ->getSearchM()->listPrivateLiveStreams(streams);

    streamZ->getSortM()->sortStreamByComments(streams);

    // If the vector contains more than 10 entries
    if (streams.size() > 10)
        streams.erase(streams.begin() + 10, streams.end());
}

void LeaderBoard::top10oldestUsersPlat(std::vector<User *> &streams) {
    // Sort with specific genres or languages
    if(streams.empty()) streamZ->getSearchM()->listUsers(streams);

    streamZ->getSortM()->sortUserDatePlatform(streams);

    // If the vector contains more than 10 entries
    if (streams.size() > 10)
        streams.erase(streams.begin() + 10, streams.end());
}
