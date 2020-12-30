//
// Created by Nuno Alves on 28/10/2020.
//

#include "Account.h"
#include "LiveStream.h"
#include "LeaderBoard.h"
#include "StreamZ.h"
#include "InvalidPassword.h"
#include "utils.h"

Account::Account(User *user, StreamZ *streamZ) {
    this->user = user;
    this->streamZ = streamZ;
    nOptions = 5;
    options = {[](){},
               [this] { listStreams(); },
               [this] { listUsers(); },
               [this] { displayStreamInfo(); },
               [this] { displayUserInfo(); },
               [this] { leaderboard(); },
               [this] { accountOptions(); }
    };
    optionDescriptions = {"Logout.",
                          "Search for current streams.",
                          "Search for users",
                          "Display stream information",
                          "Display user information",
                          "View the leaderboards.",
                          "View account options."
    };
}

void Account::run() {
    std::stringstream ss;
    uint16_t option = 1;

    while(option != 0 && user != nullptr) {
        ss.str("");
        ss << "Hello " << user->getName() << "!";
        print(ss.str());
        print();
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

        streamZ->getUserM()->removeUser(user->getNickName(),true);
        print();
        print("User deleted. We hope you enjoyed your stay.");

        user = nullptr;

        waitForKey();
    }
}

void Account::disableAccount(){
    char action;
    std::string nickName, password;

    print("Are you sure you want to deactivate your account? (Y/N) ", '\0');

    getChar(action);
    action = toupper(action);

    print();

    if(action == 'Y') {
        print("Please write your password to disable your account: ", '\0');

        getString(password);

        if(password != user->getPassword()) {
            print();
            print("Wrong Password!");

            waitForKey();

            return;
        }

        print("Please write your nickname to confirm disabling your account : ", '\0');

        while (!checkInput(nickName)) {
            print("Invalid Input! Please try again: ", '\0');
        }

        if(nickName != user->getNickName()) {
            print();
            print("Nick name did not match.");

            waitForKey();

            return;
        }

        dynamic_cast<Streamer*>(user)->disableAccount();
        print();
        print("Your account has been disabled... We hope you come back!");

        user = nullptr;

        waitForKey();
    }
}

void Account::leaderboard() {
    uint16_t option;
    print("LEADERBOARDS: ");
    print();

    print("0. Exit leaderboards.");
    print("1. Top 10 streams by likes.");
    print("2. Top 10 streams by views.");
    print("3. Top 10 long standing users.");

    print();
    print("Choose an option: ", '\0');

    while (!checkInput(option) || option < 0 || option > 3) {
        print("Invalid Option! Please try again: " , '\0');
    }

    if(option == 1) top10StreamsLikes();
    else if(option == 2) top10StreamsViews();
    else if (option == 3) top10OldestUsers();
}

void Account::searchParameters(std::vector<LiveStream *> &streams) {
    uint16_t option;
    std::string streamName;
    std::vector<genre> genres;
    std::vector<language> languages;
    unsigned age;
    std::stringstream ss;

    print("Stream Name (empty for all streams): ", '\0');

    getString(streamName);

    print("Available Stream Genres: ");
    print();

    for(auto i = (unsigned int) genre::gaming; i != genre::LASTG; i++) {
        ss.str("");
        ss << i << ". " << genreTypes[i];

        print(ss.str());
    }

    print();
    do {
        print("Choose a genre (0 to stop): ", '\0');

        while(!checkInput(option) || option < 0 || option >= LASTG) {
            print("Invalid input! Please try again: ", '\0');
        }

        if(option == 0) break;

        genres.push_back((genre) (option));
    } while(option != 0);

    print("Available Stream Languages: ");
    print();

    for(auto i = (unsigned int) language::PT_PT; i != language::LASTL; i++) {
        ss.str("");
        ss << i << ". " << languageTypes[i];

        print(ss.str());
    }

    print();
    do {
        print("Choose a language (0 to stop): ", '\0');

        while(!checkInput(option) || option < 0 || option >= LASTL) {
            print("Invalid input! Please try again: ", '\0');
        }

        if(option == 0) break;

        languages.push_back((language) (option));
    } while(option != 0);

    print("Minimum age of stream: (0 for default) ", '\0');

    while(!checkInput(age)) {
        print("Invalid Input! Please try again: ", '\0');
    }

    if(age == 0) age = VIEWER_MIN_AGE;

    streamZ->getSearchM()->listLiveStreams(streams, streamName, age, genres, languages);
}

void Account::listStreams() {
    std::vector<LiveStream*> streams;
    std::stringstream ss;

    searchParameters(streams);

    print();
    if(streams.empty()) {
        print("There are no live streams airing for the parameters selected.");

        waitForKey();

        return;
    }

    std::vector<std::string> descriptions = {
            "Sort by views descending",
            "Sort by views ascending",
            "Sort by likes descending",
            "Sort by likes ascending",
            "Sort by date started descending",
            "Sort by date started ascending"
    };

    std::vector<Option> sorting = {
            [this, &streams]{this->streamZ->getSortM()->sortStreamByViews(streams);},
            [this, &streams]{this->streamZ->getSortM()->sortStreamByViews(streams, true);},
            [this, &streams]{this->streamZ->getSortM()->sortStreamByLikes(streams);},
            [this, &streams]{this->streamZ->getSortM()->sortStreamByLikes(streams, true);},
            [this, &streams]{this->streamZ->getSortM()->sortStreamByDate(streams);},
            [this, &streams]{this->streamZ->getSortM()->sortStreamByDate(streams, true);}
    };

    sortingMethods(streams, descriptions, sorting);

    print();

    print("Here are all the current live streams: ");
    print();

    printPagedList(streams, std::function<std::string(LiveStream *)>([](LiveStream*stream){
        return stream->getShortDescription();
    }));

    print();
    waitForKey();
}

void Account::accountOptions() {
    uint16_t option;
    print("ACCOUNT OPTIONS: ");
    print();

    userType us = user->getUserType();

    print("0. Exit options panel");
    print("1. View account info.");
    print("2. Change your name.");
    print("3. Change your password.");
    print("4. Delete account. (PERMANENTLY)");
    if(us == streamer)
        print("5. Deactivate your account.");

    print("Choose an option: ", '\0');

    while (!checkInput(option) || option < 0 || option > (us != streamer ? 4 : 5)) {
        print("Invalid Option! Please try again: " , '\0');
    }

    print();

    if(option == 1) displaySelfInfo();
    else if(option==2) changeName();
    else if(option==3) changePassword();
    else if(option==4) deleteAccount();
    else if(option==5) disableAccount();
}

void Account::listUsers() {
    std::vector<User*> users;
    std::string name;

    print("User Name (empty for all users): ", '\0');

    getString(name);

    streamZ->getSearchM()->listUsers(users, name);

    std::vector<std::string> descriptions = {
            "Sort by join date descending",
            "Sort by join date ascending"
    };

    std::vector<Option> sorting = {
            [this, &users]{this->streamZ->getSortM()->sortUserDatePlatform(users);},
            [this, &users]{this->streamZ->getSortM()->sortUserDatePlatform(users, true);}
    };

    print();
    if(users.empty()) {
        print("There are no users that satisfy the selected parameters.");

        waitForKey();

        return;
    }

    sortingMethods(users, descriptions, sorting);

    print();

    print("Here are the results: ");
    print();

    printPagedList(users, std::function<std::string(User *)>([](User*userPtr){
        return userPtr->getShortDescription();
    }));

    print();
    waitForKey();
}

void Account::top10StreamsViews() {
    std::vector<LiveStream*> streams;
    std::stringstream ss;

    streamZ->getLeaderBoard()->top10StreamViews(streams);

    if(streams.empty()) {
        print("There are no streams currently airing.");

        waitForKey();

        return;
    }

    print("Here are the top 10 streams by views: ");

    print();
    for(size_t i = 0; i < streams.size(); i++) {
        ss.str("");
        ss << i+1 << ". " << streams[i]->getShortDescription() << " | Views: " << streams[i]->getNumViewers();

        print(ss.str());
    }

    print();
    waitForKey();
}

void Account::top10StreamsLikes() {
    std::vector<LiveStream*> streams;
    std::stringstream ss;

    streamZ->getLeaderBoard()->top10StreamLikes(streams);

    if(streams.empty()) {
        print("There are no streams currently airing.");

        waitForKey();

        return;
    }

    print("Here are the top 10 streams by likes: ");

    print();
    for(size_t i = 0; i < streams.size(); i++) {
        ss.str("");
        ss << i+1 << ". " << streams[i]->getShortDescription() << " | Likes: " <<
           std::setw(5) << std::left << streams[i]->getLikes() << " | Dislikes: " <<
           std::setw(5) << std::left << streams[i]->getDislikes() << " | Total: " <<
           std::setw(5) << std::left << ((long long)streams[i]->getLikes() - streams[i]->getDislikes());

        print(ss.str());
    }

    print();
    waitForKey();
}

void Account::top10OldestUsers() {
    std::vector<User*> users;
    std::stringstream ss;

    streamZ->getLeaderBoard()->top10oldestUsersPlat(users);

    print("Here are the top 10 long standing users: ");

    print();
    for(size_t i = 0; i < users.size(); i++) {
        ss.str("");
        ss << i+1 << ". " << users[i]->getShortDescription() << " | Date Joined: " << users[i]->getJoinedPlatformDate().getStringDate();

        print(ss.str());
    }

    print();
    waitForKey();
}

void Account::displayStreamInfo() {
    ID streamID;

    print("What is the ID of the stream you wish to know more about? (0 to cancel)", '\0');

    while(!checkInput(streamID)) {
        print("Invalid input! Please try again: ", '\0');
    }

    print();
    if(streamID == 0) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }

    try {
        Stream * stream = streamZ->getSearchM()->getStream(streamID);

        print(stream->getLongDescription());
    } catch(DoesNotExist<ID> &e) {
        print("Operation failed: ");
        print("No such stream with ID ", '\0');
        print(streamID);
    }

    print();
    waitForKey();
}

void Account::displayUserInfo() {
    std::string nickName;

    print("What is the nickname of the user you wish to know more about? (empty to cancel)", '\0');

    getTruncatedString(nickName);

    print();
    if(nickName.empty()) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }

    try {
        User * userPtr = streamZ->getSearchM()->getUser(nickName);

        print(userPtr->getLongDescription());
    } catch(DoesNotExist<std::string> &e) {
        print("Operation failed: ");
        print("No such user with nickname ", '\0');
        print(nickName);
    }

    print();
    waitForKey();
}

template<typename T>
void Account::sortingMethods(std::vector<T *> &toSort, std::vector<std::string> &sortDescriptions,
                             std::vector<std::function<void()>> &sortingMethods) {
    char option;
    uint16_t sorting;
    std::stringstream ss;

    print("Would you like to sort the result? (Y/N) ", '\0');

    getChar(option);
    option = toupper(option);
    size_t sortOptions = sortDescriptions.size();

    if(option == 'Y') {
        print();
        print("Available sorting methods:");
        print();

        for(size_t i = 0; i < sortOptions; i++) {
            ss.str("");

            ss << i+1 << ". " << sortDescriptions[i];

            print(ss.str());
        }

        print();
        print("Choose an option: ", '\0');

        while(!checkInput(sorting) || sorting < 1 || sorting > sortOptions) {
            print("Invalid Input! Please try again: ", '\0');
        }

        sortingMethods[sorting - 1]();
    }
}

void Account::displaySelfInfo() {
    print(user->getLongDescription(true));

    print();
    waitForKey();
}
