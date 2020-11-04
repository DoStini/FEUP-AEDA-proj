//
// Created by Nuno Alves on 28/10/2020.
//

#include "AdminAcc.h"
#include "Admin.h"
#include "StreamZ.h"

AdminAcc::AdminAcc(User *admin, StreamZ * streamZ) : Account(admin, streamZ){
    if(Admin * ad = dynamic_cast<Admin*>(admin)) {
        this->admin = ad;
    } else {
        throw WrongUserTypeException(userType::admin);
    }

    options.insert(options.begin()+3, {
       std::bind(&AdminAcc::removeUser, this),
       std::bind(&AdminAcc::removeStream, this)
    });
    optionDescriptions.insert(optionDescriptions.begin()+3, {
        "Delete a user from the platform.",
        "Delete a stream from the platform."
    });
    nOptions=options.size();
}

void AdminAcc::removeUser() {
    std::string nickName;
    std::stringstream ss;

    print("What is the nickname of the user you wish to delete? (empty to cancel) ", '\0');

    getTruncatedString(nickName);

    print();
    if(nickName.empty()) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }
    else if(nickName == admin->getNickName()) {
        print("To delete your own account, please use the correct option in the menu");

        waitForKey();

        return;
    }

    try {
        streamZ->getAdminOps()->removeUser(nickName);

        print("Operation success. User Terminated. It is nice to be in power :)");
    } catch (DoesNotExist<std::string> &e) {
        ss << "No such user with nickname " << nickName << ".";
        print("Operation Failed: ");
        print(ss.str());
    }

    waitForKey();
}

void AdminAcc::removeStream() {
    ID streamId;
    std::stringstream ss;

    print("What is the ID of the stream you wish to delete? (0 to cancel) ", '\0');

    while(!checkInput(streamId)) {
        print("Invalid ID. Please try again: ", '\0');
    }

    print();
    if(streamId == 0) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }

    try {
        streamZ->getAdminOps()->removeStream(streamId);

        print("Operation success.");
    } catch (DoesNotExist<ID> &e) {
        ss << "No such stream with ID " << streamId << ".";
        print("Operation Failed: ");
        print(ss.str());
    }

    waitForKey();
}

void AdminAcc::statistics() {
    uint16_t option;
    print("STATISTICS: ");
    print();

    print("0. Exit statistics panel.");
    print("1. Number of streams airing.");
    print("2. Number of views per stream.");
    print("3. Most viewed stream genre.");
    print("3. Most viewed stream language.");

    print();
    print("Choose an option: ", '\0');

    while (!checkInput(option) || option < 0 || option > 3) {
        print("Invalid Option! Please try again: " , '\0');
    }

    //TODO change to actual leaderboard
    //if(option == 1) streamZ->getLeaderboard()->top10StreamLikes();
    //else if(option == 2) streamZ->getLeaderboard()->top10StreamViews();
    //else if (option == 3) streamZ->getLeaderboard()->top10OldestUsers();
}
