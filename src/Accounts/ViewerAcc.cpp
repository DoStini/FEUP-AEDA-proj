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
        std::bind(&ViewerAcc::giveFeedback, this)
    });
    optionDescriptions.insert(optionDescriptions.begin()+2,{
        "Join a stream with a stream ID.",
        "Leave the stream you are currently watching.",
        "Give feedback to current stream."
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

    //TODO NEED TO CHECK IF VIEWER IS WATCHING A PRIVATE STREAM SO WE CAN ASK IF THEY WANT TO GIVE A COMMENT
    // HOW TO DO THAT?
    // if(viewer->)

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
