//
// Created by andremoreira9 on 26/10/20.
//

#include <PublicStream.h>
#include "StreamZ.h"
#include "utils.h"



void StreamZ::init() {

    //readFromFile();

    sortingManager = new SortingManager(this);
    searchManager = new SearchManager(this);
    userManager = new UserManager(this);
    leaderboard = new LeaderBoard;
    dataBase = Database();
}

void StreamZ::shutdown() {
    //backupData();
    delete sortingManager;
    delete searchManager;
    delete userManager;
    delete leaderboard;
}

SortingManager *StreamZ::getSortM() {
    return sortingManager;
}

SearchManager *StreamZ::getSearchM() {
    return searchManager;
}

UserManager *StreamZ::getUserM() {
    return userManager;
}

void StreamZ::run() {
    char title[] = {
            "   SSSSSSSSSSSSSSS      tttt                                                                                         ZZZZZZZZZZZZZZZZZZZ\n"
            " SS:::::::::::::::S  ttt:::t                                                                                         Z:::::::::::::::::Z\n"
            "S:::::SSSSSS::::::S  t:::::t                                                                                         Z:::::::::::::::::Z\n"
            "S:::::S     SSSSSSS  t:::::t                                                                                         Z:::ZZZZZZZZ:::::Z\n"
            "S:::::S        ttttttt:::::ttttttt   rrrrr   rrrrrrrrr       eeeeeeeeeeee    aaaaaaaaaaaaa      mmmmmmm    mmmmmmm   ZZZZZ     Z:::::Z\n"
            "S:::::S        t:::::::::::::::::t   r::::rrr:::::::::r    ee::::::::::::ee  a::::::::::::a   mm:::::::m  m:::::::mm         Z:::::Z\n"
            " S::::SSSS     t:::::::::::::::::t   r:::::::::::::::::r  e::::::eeeee:::::eeaaaaaaaaa:::::a m::::::::::mm::::::::::m       Z:::::Z\n"
            "  SS::::::SSSSStttttt:::::::tttttt   rr::::::rrrrr::::::re::::::e     e:::::e         a::::a m::::::::::::::::::::::m      Z:::::Z\n"
            "    SSS::::::::SS    t:::::t          r:::::r     r:::::re:::::::eeeee::::::e  aaaaaaa:::::a m:::::mmm::::::mmm:::::m     Z:::::Z\n"
            "       SSSSSS::::S   t:::::t          r:::::r     rrrrrrre:::::::::::::::::e aa::::::::::::a m::::m   m::::m   m::::m    Z:::::Z\n"
            "            S:::::S  t:::::t          r:::::r            e::::::eeeeeeeeeee a::::aaaa::::::a m::::m   m::::m   m::::m   Z:::::Z\n"
            "            S:::::S  t:::::t    ttttttr:::::r            e:::::::e         a::::a    a:::::a m::::m   m::::m   m::::mZZZ:::::Z     ZZZZZ\n"
            "SSSSSSS     S:::::S  t::::::tttt:::::tr:::::r            e::::::::e        a::::a    a:::::a m::::m   m::::m   m::::mZ::::::ZZZZZZZZ:::Z\n"
            "S::::::SSSSSS:::::S  tt::::::::::::::tr:::::r             e::::::::eeeeeeeea:::::aaaa::::::a m::::m   m::::m   m::::mZ:::::::::::::::::Z\n"
            "S:::::::::::::::SS     tt:::::::::::ttr:::::r              ee:::::::::::::e a::::::::::aa:::am::::m   m::::m   m::::mZ:::::::::::::::::Z\n"
            " SSSSSSSSSSSSSSS         ttttttttttt  rrrrrrr                eeeeeeeeeeeeee  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmmZZZZZZZZZZZZZZZZZZZ\n"
    };
    uint16_t option;

    print(title);
    print();
    print("Welcome to StreamZ!");

    print();
    while (option!=3) {
        print("Available Options:");
        print("1. Login");
        print("2. Register");
        print("3. Exit");

        print();
        print("Choose an option: ", '\0');

        while (!checkInput(option) || option < 1 || option > 3) {
            print("Invalid Option! Please try again: " , '\0');
        }

        print(LINE_BREAK);

        if(option == 1) login();


        print(LINE_BREAK);
    }

    print();
    print("Thank you for choosing StreamZ!");

    waitForKey();
}

void StreamZ::login() {
    std::string name;
    std::string password;
    bool isUser = false;
    while(!isUser) {
        print("Nick Name: ", '\0');

        while(!checkInput(name)) {
            print("Invalid Input! Please try again: " , '\0');
        }

        isUser = userManager->userExists(name);

        if(!isUser) {
            print("User does not exist! Please try again: ", '\0');
        }
    }

    User * user = searchManager->getUser(name);
    userType type = user->getInfo();

    std::string realPassword = user->getPassword();

    print("Password: ", '\0');

    while(!checkInput(password)) {
        print("Invalid Input! Please try again: " , '\0');
    }

    if(realPassword != password) {
        print();
        print("Wrong password! Login failed.");
        print();

        waitForKey();

        return;
    }

    if(type == viewer) {
        if(Viewer * userViewer = dynamic_cast<Viewer*>(user)) {
            // Instantiate Account
            return;
        }
    } else if(type = streamer) {
        if(Streamer * userStreamer = dynamic_cast<Streamer *>(user)) {
            // Instantiate Account
            return;
        }
    } else if(type = admin) {
        if(Admin * userStreamer = dynamic_cast<Admin *>(user)) {
            // Instantiate Account
            return;
        }
    }

    print("Error logging in.");
}


Database &StreamZ::getDatabase() {
    return dataBase;
}
