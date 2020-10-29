//
// Created by Nuno Alves on 28/10/2020.
//

#include "Account.h"
#include "LiveStream.h"
#include "StreamZ.h"
#include "InvalidPassword.h"

Account::Account(User *user, StreamZ *streamZ) {
    this->user = user;
    this->streamZ = streamZ;
    nOptions = 5;
    options = {[](){},
               std::bind(&Account::listStreams, this),
               std::bind(&Account::changeName, this),
               std::bind(&Account::changePassword, this),
               std::bind(&Account::deleteAccount, this)};
    optionDescriptions = {"Logout.",
                          "List all current streams.",
                          "Change your Name.",
                          "Change your password.",
                          "Delete account."};
}

void Account::run() {
    std::stringstream ss;
    uint16_t option = 1;

    while(option != 0 && user != nullptr) {
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

void Account::changePassword() {
    std::string oldPassword;
    std::string newPassword;

    print("Please input your current password: ", '\0');

    getString(oldPassword);

    if(oldPassword != user->getPassword()) {
        print();
        print("Wrong Password!");

        waitForKey();

        return;
    }

    print("Please input your new password: ", '\0');

    getString(oldPassword);

    print("Enter your new password: ", '\0');

    getString(newPassword);

    print();
    if(oldPassword != newPassword) {
        print("Passwords were not the same!");

        waitForKey();

        return;
    }

    try {
        user->changePassword(newPassword);

        print("Success changing password!");
    } catch (InvalidPassword &ex) {
        print("An invalid password was used.");
    }

    waitForKey();
}

void Account::changeName() {
    std::string newName;

    print("What will be your new name?");

    getString(newName);

    user->changeName(newName);

    print("Success changing your name!");

    waitForKey();
}

void Account::listStreams() {
    char action;
    unsigned order = 1, page = 1;
    std::stringstream ss;

    std::vector<LiveStream *> liveStreams = streamZ->getSearchM()->listStreams();
    if(liveStreams.size() == 0) {
        print("There are no live streams airing.");

        waitForKey();

        return;
    }
    auto it = liveStreams.begin();

    print("Here are all the current live streams: ");
    print();

    while(action != KEY_ESC || it != liveStreams.end()) {
        ss.str("");
        ss << "Page " << page << ": ";
        print(ss.str());
        print();

        for(int _ = 0; _ < 10 && it != liveStreams.end(); order++, it++, _++) {
            ss.str("");
            ss << order << ". " << (*it)->getTitle();
        }

        if(it == liveStreams.end()) {
            print();
            print("End of list.");

            waitForKey();
        }

        print();
        print("Press ENTER to show more streams, press ESC to leave.");

        getChar(action);

        page++;
    }
}

void Account::deleteAccount() {
    char action;
    std::string nickName, password;

    print("Are you sure you want to delete your account? (Y/N) ", '\0');

    getChar(action);
    action = toupper(action);

    print();

    if(action == 'Y') {
        print("Please write your password to delete your account: ", '\0');

        getString(password);

        if(password != user->getPassword()) {
            print();
            print("Wrong Password!");

            waitForKey();

            return;
        }

        print("Please write your nickname to confirm the deletion: ", '\0');

        while (!checkInput(nickName)) {
            print("Invalid Input! Please try again: ", '\0');
        }

        if(nickName != user->getNickName()) {
            print();
            print("Nick name did not match.");

            waitForKey();

            return;
        }

        delete user;
        print();
        print("User deleted. We hope you enjoyed your stay.");

        user = nullptr;

        waitForKey();
    }
}
