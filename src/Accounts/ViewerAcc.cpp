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

    nOptions += 1;
    options.insert(options.begin()+2, {
        std::bind(&ViewerAcc::joinStreamById, this)
    });
    optionDescriptions.insert(optionDescriptions.begin()+2,{
        "Join a stream with a stream ID."
    });
}

void ViewerAcc::joinStreamById() {
    ID streamId;

    print("What is the stream ID? ", '\0');

    while (!checkInput(streamId)) {
        print("Invalid input! Please try again: ", '\0');
    }

    try {
        viewer->joinStream(streamId);
    }

}
