//
// Created by Nuno Alves on 28/10/2020.
//

#include "ViewerAcc.h"
#include "Viewer.h"
#include "StreamZ.h"
#include "OrdersEmptyException.h"
#include "OrdersFullException.h"
#include "NoSuchOrderException.h"
#include <sstream>
#include<functional>

ViewerAcc::ViewerAcc(User *user, StreamZ * streamZ) : Account(user, streamZ){
    if(auto * viewerPtr = dynamic_cast<Viewer*>(user)) {
        this->viewer = viewerPtr;
    } else {
        throw WrongUserTypeException(userType::viewer);
    }


    options.insert(options.begin()+5, {
        [this] { findStreamFollowing(); },
        [this] { displayWatchingInfo();},
        [this] { joinStreamById(); },
        [this] { leaveStream(); },
        [this] { giveFeedback(); },
        [this] { giveComment(); },
        [this] { listFollowingStreamers(); },
        [this] { followStreamer(); },
        [this] { unfollowStreamer(); },
        [this] { displayHistory(); },
        [this] { orderMerch(); },
        [this] { removeOrder(); },
        [this] { makeDonation();}
    });
    optionChecks[5] = optionChecks[11] = optionChecks[13] =
            [this]() {return !this->viewer->getFollowingStreamers().empty();};
    optionChecks[7] = [this]() {return !this->viewer->watching();};
    optionChecks[8] = optionChecks[9] = optionChecks[6] = [this]() {return this->viewer->watching();};
    optionChecks[10] = [this]() { return this->checkWatchingPrivate();};
    optionDescriptions.insert(optionDescriptions.begin()+5,{
        "List all live streams from the streamers you follow.",
        "Display information about the stream you are watching",
        "Join a stream with a stream ID.",
        "Leave the stream you are currently watching.",
        "Give feedback to current stream.",
        "Write a comment to the current stream.",
        "List all the streamers you follow.",
        "Follow a streamer.",
        "Unfollow a streamer.",
        "Display your watch history.",
        "Order Merch.",
        "Remove a placed order.",
        "Make donation"
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

        print("Operation success!");
    } catch(AlreadyInStreamException &e) {
        print("Operation failed: ");
        print(e);
    } catch (DoesNotExist<ID> &e) {
        ss << "No such stream with ID " << streamId;
        print("Operation failed: "); //No such stream
        print(ss.str());
    } catch (RestrictedAgeException &e) {
        print("Operation failed: "); //No such stream
        print(e);
    } catch (RestrictedStreamException &e) {
        print("Operation failed: "); //No such stream
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

    print("Do you want to press the like or the dislike button? (Y for like, N for dislike, 0 to remove) ", '\0');

    getChar(input);
    input = toupper(input);

    print();
    if(input == 'N') {
        viewer->giveFeedBack(feedback::dislike);

        print("Disliked!");
    } else if(input == 'Y') {
        viewer->giveFeedBack(feedback::like);

        print("Liked!");
    } else {
        viewer->giveFeedBack(feedback::none);

        print("Your feedback has been removed.");
    }

    waitForKey();
}

bool ViewerAcc::checkWatchingPrivate() const {
    if(!this->viewer->watching()) return false;

    ID streamId = this->viewer->getCurrWatching();
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
    if(comment.empty()) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }

    try {
        viewer->giveFeedBack(comment);

        print("Operation success!");
    } catch (NotInStreamException &e) {
        print("Operation failed: ");
        print(e);
    } catch (NotPrivateStreamException &e) {
        print("Operation failed: ");
        print(e);
    }

    waitForKey();
}

void ViewerAcc::findStreamFollowing() {
    const std::vector<std::string> streamerNicks = viewer->getFollowingStreamers();
    std::vector<LiveStream *> streams;
    streamZ->getSearchM()->listLiveStreamsByStreamers(streams, streamerNicks);

    if(streams.empty()) {
        print("There are no live streams airing from the streamers you follow.");

        waitForKey();

        return;
    }

    print("Here are all the current live streams from the streamers you follow: ");
    print();

    printPagedList(streams, std::function<std::string(LiveStream *)>([](LiveStream*stream){
        return stream->getShortDescription();
    }));

    print();
    waitForKey();
}

void ViewerAcc::followStreamer() {
    std::string nickName;

    print("What is the nickname of the streamer you wish to follow? (empty to cancel) ", '\0');

    getTruncatedString(nickName);

    print();
    if(nickName.empty()) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }

    try {
        viewer->followStreamer(nickName);

        print("Operation success!");
    } catch (FollowStreamerException &e) {
        print("Operation failed: ");
        print(e);
    } catch (DoesNotExist<std::string> &e) {
        print("Operation failed: ");
        print("No such streamer with nickname ", '\0');
        print(nickName);
    }

    waitForKey();

}

void ViewerAcc::unfollowStreamer() {
    std::string nickName;

    print("What is the nickname of the streamer you wish to unfollow? (empty to cancel) ", '\0');

    getTruncatedString(nickName);

    print();
    if(nickName.empty()) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }

    try {
        viewer->unFollowStreamer(nickName);

        print("Operation success!");
    } catch (FollowStreamerException &e) {
        print("Operation failed: ");
        print(e);
    } catch (DoesNotExist<std::string> &e) {
        print("Operation failed: ");
        print("No such streamer with nickname: ", '\0');
        print(nickName);
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

    printPagedList(following, std::function<std::string(std::string)>([this](std::string nick){
        Streamer * streamer = dynamic_cast<Streamer *>(this->streamZ->getSearchM()->getUser(nick));
        return streamer->getShortDescription();
    }));

    print();
    waitForKey();
}

void ViewerAcc::displayHistory() {
    std::vector<ID> history = viewer->getHistory();

    if(history.empty()) {
        print("You haven't watched any streams.");

        waitForKey();

        return;
    }

    print("Here are all the streams you have watched: ");
    print();

    printPagedList(history, std::function<std::string(ID)>([this](ID streamID){
        auto * stream = dynamic_cast<Stream *>(this->streamZ->getSearchM()->getStream(streamID));
        return stream->getShortDescription();
    }));

    print();
    waitForKey();
}

void ViewerAcc::displayWatchingInfo() {
    if(!viewer->watching()) {
        print("Operation failed:");
        print("You aren't watching any stream!");

        print();
        waitForKey();
        return;
    }

    Stream * watching = streamZ->getSearchM()->getStream(viewer->getCurrWatching());
    print(watching->getLongDescription());

    print();
    waitForKey();
}


void ViewerAcc::makeDonation() {
    std::string nickName;
    int amount, evaluation;

    print("What is the nickname of the streamer you wish to donate? (empty to cancel) ", '\0');

    getTruncatedString(nickName);

    print();
    if(nickName.empty()) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }

    print("What is the amount of money to donate? ", '\0');

    while (!checkInput(amount)) {
        print("Invalid input! Please try again: ", '\0');
    }


    print("What is the evaluation? ", '\0');

    while (!checkInput(evaluation)) {
        print("Invalid input! Please try again: ", '\0');
    }

    try {
        streamZ->getDonationManager()->creatDonation(nickName,amount,evaluation);

        print("Operation success!");

    } catch (AlreadyExists<DonationItem> &e) {
        print("Operation failed: ");
        print(e);
    } catch (DoesNotExist<std::string> &e) {
        print("Operation failed: ");
        print("No such streamer with nickname: ", '\0');
        print(nickName);
    } catch (NotInRangeValue &e) {
        print("Operation failed: ");
        print(e);
    }

    waitForKey();
}

void ViewerAcc::orderMerch() {
    std::string nickName;

    print("What is the nickname of the streamer you wish to buy merch from? (empty to cancel) ", '\0');

    getTruncatedString(nickName);

    print();
    if(nickName.empty()) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }

    int num, availability;

    print("What is the number of merch you wish to buy? ", '\0');

    while (!checkInput(num) || num <= 0) {
        print("Invalid input! Please try again: ", '\0');
    }

    print("What is your purchase availability? ", '\0');

    while (!checkInput(availability) || availability < 0) {
        print("Invalid input! Please try again: ", '\0');
    }

    print();
    try {
        viewer->orderMerch(nickName, num, availability);

        print("Operation success!");
    } catch (OrdersFullException & e) {
        print("Operation failed: ");
        print(e);
    } catch (DoesNotExist<std::string> & e) {
        print("Operation failed: ");
        print("No such streamer with nickname: ", '\0');
        print(e);
    }

    waitForKey();
}


void ViewerAcc::removeOrder() {
    std::string nickName;
    std::stringstream  ss;

    print("What is the nickname of the streamer you wish to remove an order from? (empty to cancel) ", '\0');

    getTruncatedString(nickName);

    print();
    if(nickName.empty()) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }

    print();
    try {
        MerchandisingOrder merchandisingOrder = viewer->removeOrder(nickName);

        print("Operation success!");
        ss << merchandisingOrder << " removed.";
        print(ss.str());
    } catch (NoSuchOrderException & e) {
        print("Operation failed: ");
        print(e);
    } catch (DoesNotExist<std::string> & e) {
        print("Operation failed: ");
        print("No such streamer with nickname: ", '\0');
        print(e);
    }

    waitForKey();
}
