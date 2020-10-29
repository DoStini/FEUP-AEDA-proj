//
// Created by Nuno Alves on 28/10/2020.
//

#include "ViewerAcc.h"
#include "Viewer.h"
#include <sstream>

ViewerAcc::ViewerAcc(User *user, StreamZ * streamZ) : Account(user, streamZ){
    if(Viewer * viewer = dynamic_cast<Viewer*>(user)) {
        this->viewer = viewer;
    } else {
        throw WrongUserTypeException(UserType::viewer);
    }
}

void ViewerAcc::run() {
    std::stringstream ss;
    uint16_t option = 1;

    while(option != 0) {
        print("Available Options:");
        for(unsigned i = 0; i < nOptions; i++) {
            ss.str("");

            ss << i << ". " << optionDescriptions[i];
            print(ss.str());
        }

        print();
        print("Choose an option: ", '\0');

        while (!checkInput(option) || option < 0 || option >= nOptions) {
            print("Invalid Option! Please try again: " , '\0');
        }
        if(option == 0) break;

        print(LINE_BREAK);

        (options[option])();

        print(LINE_BREAK);
    }

    print();
    print("Goodbye!");
    waitForKey();
}
