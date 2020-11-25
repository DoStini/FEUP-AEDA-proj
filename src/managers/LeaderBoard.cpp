//
// Created by andremoreira9 on 27/10/20.
//

#include "LeaderBoard.h"
#include "StreamZ.h"

LeaderBoard::LeaderBoard(StreamZ *streamZ) : streamZ(streamZ) {}

void LeaderBoard::top10StreamViews(std::vector<LiveStream *> &streams) const{

    // Sort with specific genres or languages
    if(streams.empty()) streamZ->getSearchM()->listLiveStreams(streams);

    streamZ->getSortM()->sortStreamByViews(streams);

    // If the vector contains more than 10 entries
    if (streams.size() > 10)
        streams.erase(streams.begin() + 10, streams.end());
}

void LeaderBoard::top10StreamLikes(std::vector<LiveStream *> &streams) const{
    // Sort with specific genres or languages
    if(streams.empty()) streamZ->getSearchM()->listLiveStreams(streams);

    // Changed this line of code after submission
    // Was like this:
    //streamZ->getSortM()->sortStreamByLikes(streams, true);

    // Should be this
    // Caused by debugging session before submission

    streamZ->getSortM()->sortStreamByLikes(streams);

    // If the vector contains more than 10 entries
    if (streams.size() > 10)
        streams.erase(streams.begin() + 10, streams.end());
}

void LeaderBoard::top10StreamComments(std::vector<PrivateStream *> &streams) const{
    // Sort with specific genres or languages
    if(streams.empty()) streamZ->getSearchM()->listPrivateLiveStreams(streams);

    streamZ->getSortM()->sortStreamByComments(streams);

    // If the vector contains more than 10 entries
    if (streams.size() > 10)
        streams.erase(streams.begin() + 10, streams.end());
}

void LeaderBoard::top10oldestUsersPlat(std::vector<User *> &streams) const{
    // Sort with specific genres or languages
    if(streams.empty()) streamZ->getSearchM()->listUsers(streams);

    streamZ->getSortM()->sortUserDatePlatform(streams);

    // If the vector contains more than 10 entries
    if (streams.size() > 10)
        streams.erase(streams.begin() + 10, streams.end());
}
