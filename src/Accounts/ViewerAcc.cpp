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
        std::bind(&ViewerAcc::joinStreamById, this),
        std::bind(&ViewerAcc::leaveStream, this),
        std::bind(&ViewerAcc::giveFeedback, this),
        std::bind(&ViewerAcc::giveComment, this)
    });
    optionChecks[2] = [this]() {return !this->viewer->watching();};
    optionChecks[3] = [this]() {return this->viewer->watching();};
    optionChecks[4] = [this]() {return this->viewer->watching();};
    optionChecks[5] = [this]() { return this->checkWatchingPrivate();};
    optionDescriptions.insert(optionDescriptions.begin()+2,{
        "Join a stream with a stream ID.",
        "Leave the stream you are currently watching.",
        "Give feedback to current stream.",
        "Write a comment to the current stream."
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
