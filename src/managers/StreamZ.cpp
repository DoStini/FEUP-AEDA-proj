//
// Created by andremoreira9 on 26/10/20.
//

#include <PublicStream.h>
#include "StreamZ.h"
#include "utils.h"
#include "InvalidPassword.h"



void StreamZ::init() {

    //readFromFile();

    sortingManager = new SortingManager(this);
    searchManager = new SearchManager(this);
    userManager = new UserManager(this);
    leaderboard = new LeaderBoard;
    adminOps = new AdminOps(this);
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

AdminOps *StreamZ::getAdminOps() {
    return adminOps;
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
        else if(option == 2) registerUser();
        else break;

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
            print("User does not exist! Please try again.");
        }
    }

    User * user = nullptr;

    try {
        user = searchManager->getUser(name);
    } catch (DoesNotExist<std::string> &ex) {
        print();
        print("That user does not exist.");

        waitForKey();

        return;
    }

    UserType type = user->getInfo();

    std::string realPassword = user->getPassword();

    print("Password: ", '\0');

    getString(password);

    if(realPassword != password) {
        print();
        print("Wrong password! Login failed.");
        print();

        waitForKey();

        return;
    }
    Account * account = nullptr;

    try {
        if(type == viewer) {
            account = new ViewerAcc(user, this);
        } else if(type == streamer) {
            account = new StreamerAcc(user, this);
        } else if(type == admin) {
            account = new AdminAcc(user, this);
        }

        print();
        print("Success logging in!");

        waitForKey();

    } catch (WrongUserTypeException &ex) {
        print("Error logging in.");

        waitForKey();

        print(LINE_BREAK);

        return;
    }

    print(LINE_BREAK);

    account->run();
    delete account;
}


Database &StreamZ::getDatabase() {
    return dataBase;
}

void StreamZ::registerUser() {
    uint16_t type;
    std::string userName;
    std::string nickName;
    std::string password;
    std::string date;
    Date dateObj;

    print("What type of user are you?");
    print("1. Viewer");
    print("2. Streamer");

    print();
    print("Choose an option: ", '\0');

    while (!checkInput(type) || type < 1 || type > 2) {
        print("Invalid Option! Please try again: " , '\0');
    }

    UserType uType = (UserType) (type - 1);

    print("What will be your nick name? (used to login) ", '\0');

    while (!checkInput(nickName)) {
        print("Invalid Input! Please try again: " , '\0');
    }

    print("What will be your user name? (used to display) ", '\0');

    getString(userName);

    print("What is the date you were born? (used to calculate your age)");
    print("(Format: YYYY/MM/DD or YYYY-MM-DD or YYYY MM DD) ", '\0');

    do {
        try {
            getString(date);
            dateObj = Date(date);

            break;
        } catch (BadDateFormat &ex) {
            print("Date was in a wrong format. Please try again: ", '\0');
        } catch (InvalidDate &ex) {
            print("Date is not valid! Please try again: ", '\0');
        }
    } while(true);

    print("What will be your password? ", '\0');

    getString(password);

    print();
    try {
        if(uType == viewer) {
            userManager->createViewer(userName, nickName, dateObj, password);
        } else if(uType == streamer) {
            userManager->createStreamer(userName, nickName, dateObj, password);
        }

        print("Success!!");

        waitForKey();

        return;
    } catch (RestrictedAgeException &ex) {
        print("You are not old enough to create an account: ");
        std::cout << ex;

    } catch (InvalidPassword &ex) {
        print("An invalid password was used.");

        //TODO CATCH ALREADY EXISTS
//    } catch (Alread) {
//
    }

    print("Register Failed.");

    waitForKey();
}
