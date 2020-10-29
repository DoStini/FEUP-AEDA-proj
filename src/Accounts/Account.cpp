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

void Account::changePassword() {
    std::string oldPassword;
    std::string newPassword;

    print("Please input your last password: ", '\0');

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
