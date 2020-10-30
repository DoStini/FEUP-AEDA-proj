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
        std::bind(&ViewerAcc::leaveStream, this)
    });
    optionDescriptions.insert(optionDescriptions.begin()+2,{
        "Join a stream with a stream ID.",
        "Leave the stream you are currently watching."
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
