//
// Created by adbp on 18/10/2020.
//

#include "PrivateStream.h"

#include <utility>

#include "User.h"
#include "StreamZ.h"

PrivateStream::PrivateStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick,
                                unsigned int minAge, unsigned int maxViewers) : LiveStream(std::move(title),
                                    streamLanguage, streamGenre,std::move(streamerNick), minAge), maxViewers(maxViewers) {}

unsigned PrivateStream::getNumberComments() {
    return comments.size();
}

streamType PrivateStream::getStreamType() const {
    return privateType;
}

bool PrivateStream::isValidUser(const std::string& userNick) {
    return (std::find(whitelist.begin(),whitelist.end(),userNick) != whitelist.end());
}

void PrivateStream::addValidUser(const std::string& userNick) {
<<<<<<< HEAD
    if( isValidUser(userNick) )
=======
    if(!streamZ->getSearchM()->userExists(userNick))
        throw DoesNotExist<std::string>(userNick);
    if(std::find(whitelist.begin(),whitelist.end(),userNick) != whitelist.end())
>>>>>>> 913997ff7dfb43cdfe2091050b4d128f64f10c3f
        throw AlreadyInWhiteListException(userNick,this->getStreamId()) ;
    whitelist.push_back(userNick);
}

void PrivateStream::removeValidUser(const std::string &userNick) {
<<<<<<< HEAD

    if(!isValidUser(userNick))
        throw NotInWhiteListException(userNick, streamId);

    whitelist.erase(find(whitelist.begin(),whitelist.end(),userNick));
=======
    auto it = find(whitelist.begin(),whitelist.end(),userNick);
    if(it == whitelist.end())
        throw NotInStreamException(userNick);
    else {
        whitelist.erase(it);

        auto viewer = (Viewer *) streamZ->getSearchM()->getUser(userNick);
        if (viewer->getCurrWatching() == streamId)
            viewer->leaveStream();
    }
>>>>>>> 913997ff7dfb43cdfe2091050b4d128f64f10c3f
}

int PrivateStream::getWhitelistSize() const {
    return whitelist.size();
}

void PrivateStream::addComment(const std::string & text,const std::string & userNick) {
    Comment comment(text,userNick);
    comments.push_back(comment);
}

unsigned int PrivateStream::getMaxViewers() const {
    return maxViewers;
}

void PrivateStream::addViewer(const std::string &viewerNick) {
    if(this->getNumViewers() == maxViewers)
        throw MaxViewersReach(streamId, maxViewers);
    else
        streamViewers.push_back(viewerNick);
}


