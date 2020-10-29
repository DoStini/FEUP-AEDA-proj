//
// Created by Nuno Alves on 28/10/2020.
//

#include "Account.h"
#include "StreamZ.h"
#include "InvalidPassword.h"

Account::Account(User *user, StreamZ *streamZ) {
    this->user = user;
    this->streamZ = streamZ;
    nOptions = 3;
    options = {[](){},
               std::bind(&Account::changeName, this),
               std::bind(&Account::changePassword, this)};
    optionDescriptions = {"Logout.",
                          "Change your Name.",
                          "Change your password."};
}

void Account::run() {
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
