//
// Created by Nuno Alves on 28/10/2020.
//

#include "ViewerAcc.h"
#include "Viewer.h"
#include "StreamZ.h"
#include <sstream>
#include<functional>

ViewerAcc::ViewerAcc(User *user, StreamZ * streamZ) : Account(user, streamZ){
    if(Viewer * viewer = dynamic_cast<Viewer*>(user)) {
        this->viewer = viewer;
    } else {
        throw WrongUserTypeException(UserType::viewer);
    }


    options.insert(options.begin()+2, {
        std::bind(&ViewerAcc::findStreamFollowing, this),
        std::bind(&ViewerAcc::joinStreamById, this),
        std::bind(&ViewerAcc::leaveStream, this),
        std::bind(&ViewerAcc::giveFeedback, this),
        std::bind(&ViewerAcc::giveComment, this),
        std::bind(&ViewerAcc::listFollowingStreamers, this),
        std::bind(&ViewerAcc::followStreamer, this),
        std::bind(&ViewerAcc::unfollowStreamer, this)
    });
    optionChecks[2] = [this]() {return !this->viewer->getFollowingStreamers().empty();};
    optionChecks[3] = [this]() {return !this->viewer->watching();};
    optionChecks[4] = [this]() {return this->viewer->watching();};
    optionChecks[5] = [this]() {return this->viewer->watching();};
    optionChecks[6] = [this]() { return this->checkWatchingPrivate();};
    optionChecks[7] = [this]() {return !this->viewer->getFollowingStreamers().empty();};
    optionChecks[9] = [this]() {return !this->viewer->getFollowingStreamers().empty();};
    optionDescriptions.insert(optionDescriptions.begin()+2,{
        "List all live streams from the streamers you follow.",
        "Join a stream with a stream ID.",
        "Leave the stream you are currently watching.",
        "Give feedback to current stream.",
        "Write a comment to the current stream.",
        "List all the streamers you follow.",
        "Follow a streamer.",
        "Unfollow a streamer."
    });
    nOptions = options.size();
}

void ViewerAcc::joinStreamById() {
    ID streamId;
    std::stringstream ss;

    print("What is the stream ID? ", '\0');

    while (!checkInput(streamId)) {
        print("Invalid input! Please try again: ", '\0');
    }

    print();
    try {
        viewer->joinStream(streamId);

        print("Join Successful");
    } catch(AlreadyInStreamException &e) {
        print("Join Failed: ");
        print(e);
    } catch (DoesNotExist<ID> &e) {
        ss << "No such stream with ID " << streamId;
        print("Join Failed: "); //No such stream
        print(ss.str());
    } catch (RestrictedAgeException &e) {
        print("Join Failed: "); //No such stream
        print(e);
    } catch (RestrictedStreamException &e) {
        print("Join Failed: "); //No such stream
        print(e);
    }

    waitForKey();
}

void ViewerAcc::leaveStream() {
    try {
        viewer->leaveStream();

        print("Left the stream!");
    } catch (NotInStreamException &e) {
        print(e);
    }

    waitForKey();
}

void ViewerAcc::giveFeedback() {
    char input;
    if(!viewer->watching()) {
        print("Failed to give feedback. You are not watching any stream.");

        waitForKey();
        return;
    }

    print("Do you want to press the like or the dislike button? (Y for like, N for dislike) ", '\0');

    getChar(input);
    input = toupper(input);

    print();
    if(input == 'N') {
        viewer->giveFeedBack(feedback::dislike);

        print("Disliked!");
    } else {
        viewer->giveFeedBack(feedback::like);

        print("Liked!");
    }

    waitForKey();
}

bool ViewerAcc::checkWatchingPrivate() const {
    if(!this->viewer->watching()) return false;

    ID streamId = this->viewer->getStreamID();
    Stream * stream = this->streamZ->getDatabase().getStreams()[streamId];
    return stream->getStreamType() == privateType;
}

void ViewerAcc::giveComment() {
    std::string comment;
    if(!checkWatchingPrivate()) {
        print("Failed to give feedback. You are not watching a private stream.");

        waitForKey();
        return;
    }

    print("Write your comment: (empty to cancel) ", '\0');

    getString(comment);

    print();
    if(comment.empty()) print("Operation cancelled.");
    else print("Success!");

    waitForKey();
}

void ViewerAcc::findStreamFollowing() {
    const std::vector<std::string> streamerNicks = viewer->getFollowingStreamers();
    std::vector<LiveStream *> streams;
    streamZ->getSearchM()->listLiveStreamsByStreamers(streams, streamerNicks);

    if(streams.size() == 0) {
        print("There are no live streams airing from the streamers you follow.");

        waitForKey();

        return;
    }

    print("Here are all the current live streams from the streamers you follow: ");
    print();

    // TODO CHANGE TO FUNCTION IN TYPE.
    printPagedList(streams, std::function<std::string(LiveStream *)>([](LiveStream*stream){
        std::stringstream  ss;
        ss << stream->getTitle() << " (Stream Id: " << stream->getId() << ")";
        return ss.str();
    }));
}

void ViewerAcc::followStreamer() {
    std::string nickName;

    print("What is the nickname of the streamer you wish to follow? ", '\0');

    while(!checkInput(nickName)) {
        print("Invalid nickname, please try again: ", '\0');
    }

    print();
    // TODO THIS IS NOT CHECKING IF THE STREAMER EXISTS OR NOT
    try {
        viewer->followStreamer(nickName);

        print("Success!");
    } catch (FollowStreamerException &e) {
        print(e);
    }

    waitForKey();

}

void ViewerAcc::unfollowStreamer() {
    std::string nickName;

    print("What is the nickname of the streamer you wish to unfollow? ", '\0');

    while(!checkInput(nickName)) {
        print("Invalid nickname, please try again: ", '\0');
    }

    print();
    // TODO THIS IS NOT CHECKING IF THE STREAMER EXISTS OR NOT
    try {
        viewer->unFollowStreamer(nickName);

        print("Success!");
    } catch (FollowStreamerException &e) {
        print(e);
    }

    waitForKey();
}

void ViewerAcc::listFollowingStreamers() {
    const std::vector<std::string> following = viewer->getFollowingStreamers();

    if(following.empty()) {
        print("You don't follow any streamers.");

        waitForKey();

        return;
    }

    print("Here are all the streamers you follow: ");
    print();

    // TODO CHANGE TO FUNCTION IN TYPE.
    printPagedList(following, std::function<std::string(std::string)>([this](std::string nick){
        std::stringstream  ss;
        Streamer * streamer = dynamic_cast<Streamer *>(this->streamZ->getSearchM()->getUser(nick));
        ss << streamer->getName() << " (Nickname: " << streamer->getNickName() << ")";
        return ss.str();
    }));
}
