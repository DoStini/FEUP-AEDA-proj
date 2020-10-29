//
// Created by Nuno Alves on 28/10/2020.
//

#include "Account.h"
#include "StreamZ.h"

Account::Account(User *user, StreamZ *streamZ) {
    this->user = user;
    this->streamZ = streamZ;
    options = {[](){}, std::bind(&Account::changePassword, this)};
    optionDescriptions = {"Logout.", "Change your Password."};
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

    //streamZ->getUserM()->changePassword();

    print("Success changing password!");

    waitForKey();
}
