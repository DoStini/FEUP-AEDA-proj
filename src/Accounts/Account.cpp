//
// Created by Nuno Alves on 28/10/2020.
//

#include "Account.h"
#include "LiveStream.h"
#include "StreamZ.h"
#include "InvalidPassword.h"
#include "utils.h"

static const char *languageTypes[] = {
        "Portuguese (Portugal)",
        "Portuguese (Brazil)",
        "English",
        "Spanish",
        "French",
        "German",
        "Russian",
        "Chinese",
        "Hindi",
};

static const char *genreTypes[] = {
        "Gaming",
        "Technology",
        "Music",
        "Cooking",
        "Meet & Greet"
};

Account::Account(User *user, StreamZ *streamZ) {
    this->user = user;
    this->streamZ = streamZ;
    nOptions = 5;
    options = {[](){},
               std::bind(&Account::listStreams, this),
               std::bind(&Account::listUsers, this),
               std::bind(&Account::leaderboard, this),
               std::bind(&Account::accountOptions, this)
    };
    optionDescriptions = {"Logout.",
                          "Search for current streams.",
                          "Search for users",
                          "View the leaderboards.",
                          "View account options."
    };
}

void Account::run() {
    std::stringstream ss;
    uint16_t option = 1;

    while(option != 0 && user != nullptr) {
        print("Available Options:");
        for(unsigned i = 0; i < nOptions; i++) {
            auto optionCheckIt = optionChecks.find(i);

            if(optionCheckIt == optionChecks.end() || optionCheckIt->second()) {
                ss.str("");

                ss << i << ". " << optionDescriptions[i];
                print(ss.str());
            }
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

    print();
    print("Success changing your name!");

    waitForKey();
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

void Account::leaderboard() {
    uint16_t option;
    print("LEADERBOARDS: ");
    print();

    print("0. Exit leaderboards.");
    print("1. Top 10 Streamers by likes.");
    print("2. Top 10 Streamers by views.");
    print("3. Top 10 oldest users.");

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

void Account::searchParameters(std::vector<LiveStream *> &streams) {
    uint16_t option;
    std::string streamName;
    std::vector<genre> genres;
    std::vector<language> languages;
    std::stringstream ss;

    print("Stream Name (empty for all streams): ", '\0');

    getString(streamName);

    print("Available Stream Genres: ");
    print();

    for(uint32_t i = (unsigned int) genre::gaming; i != genre::LASTG; i++) {
        ss.str("");
        ss << i + 1 << ". " << genreTypes[i];

        print(ss.str());
    }

    print();
    do {
        print("Choose a genre (0 to stop): ", '\0');

        while(!checkInput(option) || option < 0 || option > LASTG) {
            print("Invalid input! Please try again: ", '\0');
        }

        if(option == 0) break;

        genres.push_back((genre) (option + 1));
    } while(option != 0);

    print("Available Stream Languages: ");
    print();

    for(uint32_t i = (unsigned int) language::PT_PT; i != language::LASTL; i++) {
        ss.str("");
        ss << i + 1 << ". " << languageTypes[i];

        print(ss.str());
    }

    print();
    do {
        print("Choose a language (0 to stop): ", '\0');

        while(!checkInput(option) || option < 0 || option > LASTL) {
            print("Invalid input! Please try again: ", '\0');
        }

        if(option == 0) break;

        languages.push_back((language) (option + 1));
    } while(option != 0);

    streamZ->getSearchM()->listLiveStreams(streams, streamName, genres, languages);
}

void Account::listStreams() {
    std::vector<LiveStream*> streams;
    std::stringstream ss;

    searchParameters(streams);

    print();
    if(streams.size() == 0) {
        print("There are no live streams airing for the parameters selected.");

        waitForKey();

        return;
    }

    print("Here are all the current live streams: ");
    print();

    // TODO CHANGE TO FUNCTION IN TYPE.
    printPagedList(streams, std::function<std::string(LiveStream *)>([](LiveStream*stream){
        std::stringstream  ss;
        ss << stream->getTitle() << " (Stream Id: " << stream->getId() << ")";
        return ss.str();
    }));
}

void Account::accountOptions() {
    uint16_t option;
    print("ACCOUNT OPTIONS: ");
    print();

    print("0. Exit options panel");
    print("1. Change your name.");
    print("2. Change your password.");
    print("3. Delete account.");
    print();

    print("Choose an option: ", '\0');

    while (!checkInput(option) || option < 0 || option > 3) {
        print("Invalid Option! Please try again: " , '\0');
    }

    print();

    if(option==1) changeName();
    else if(option==2) changePassword();
    else if(option==3) deleteAccount();
}

void Account::listUsers() {
    std::vector<User*> users;
    std::string name;

    print("User Name (empty for all users): ", '\0');

    getString(name);

    streamZ->getSearchM()->listUsers(users, name);

    print();
    if(users.size() == 0) {
        print("There are no users that satisfy the selected parameters.");

        waitForKey();

        return;
    }

    print("Here are the results: ");
    print();

    // TODO CHANGE TO FUNCTION IN TYPE.
    printPagedList(users, std::function<std::string(User *)>([](User*user){
        std::stringstream  ss;
        ss << user->getName() << " (Nickname: " << user->getNickName() << ")";
        return ss.str();
    }));
}
