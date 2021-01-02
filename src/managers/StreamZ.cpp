//
// Created by andremoreira9 on 26/10/20.
//

#include <PublicStream.h>
#include "StreamZ.h"
#include "utils.h"
#include "InvalidPassword.h"
#include "AlreadyExists.h"
#include "LiveStream.h"
#include "BST.h"


void StreamZ::init() {
    LiveStream::lastId = NULL_STREAM;
    sortingManager = new SortingManager(this);
    searchManager = new SearchManager(this);
    userManager = new UserManager(this);
    streamManager = new StreamManager(this);
    adminOps = new AdminOps(this);
    leaderboard = new LeaderBoard(this);
    donationManager = new DonationManager(this);
    dataBase = Database();
    userManager->setOrdersSize(10);

}

void StreamZ::init(std::string fileName) {
    LiveStream::lastId = NULL_STREAM;
    sortingManager = new SortingManager(this);
    searchManager = new SearchManager(this);
    userManager = new UserManager(this);
    streamManager = new StreamManager(this);
    adminOps = new AdminOps(this);
    leaderboard = new LeaderBoard(this);
    donationManager = new DonationManager(this);
    dataBase = Database();


    try{
        readFromFile(fileName);
    }
    catch (const std::string & e) {
        print(e);
        print();
    }
}

void StreamZ::shutdown(std::string fileName) {
    backupData(fileName);
    delete sortingManager;
    delete searchManager;
    delete userManager;
    delete streamManager;
    delete leaderboard;
    delete donationManager;
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

AdminOps * StreamZ::getAdminOps() {
    return adminOps;
}

DonationManager *StreamZ::getDonationManager() const {
    return donationManager;
}

LeaderBoard *StreamZ::getLeaderBoard() {
    return leaderboard;
}

Database &StreamZ::getDatabase() {
    return dataBase;
}


StreamManager *StreamZ::getStreamManager(){
    return streamManager;
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
    while (option!=4) {
        print("Available Options:");
        print("1. Login");
        print("2. Register");
        print("3. Recover Account");
        print("4. Exit");

        print();
        print("Choose an option: ", '\0');

        while (!checkInput(option) || option < 1 || option > 4) {
            print("Invalid Option! Please try again: " , '\0');
        }

        print(LINE_BREAK);

        if(option == 1) login();
        else if(option == 2) registerUser();
        else if(option == 3) recoverAccount();
        else break;

        print(LINE_BREAK);
    }

    print();
    print("Saving state of database...");

    print();
    print("Thank you for choosing StreamZ!");

    waitForKey();
}

void StreamZ::login() {
    std::string name;
    std::string password;
    print("Nick Name: ", '\0');

    while(!checkInput(name)) {
        print("Invalid Input! Please try again: " , '\0');
    }

    User * user = nullptr;

    try {
        user = searchManager->getUser(name);
        if(user->getUserType() == streamer && !dynamic_cast<Streamer *>(user)->isActive())
        {
            print("That streamer's account is disabled. Please reactive it in the appropriate menu.");
            waitForKey();
            return;
        }
    } catch (DoesNotExist<std::string> &ex) {
        print();
        print("That user does not exist.");

        waitForKey();

        return;
    }

    userType type = user->getUserType();

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
    print("3. Admin");

    print();
    print("Choose an option: ", '\0');

    while (!checkInput(type) || type < 1 || type > 3) {
        print("Invalid Option! Please try again: " , '\0');
    }

    userType uType = (userType) type;

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

    while (!checkInput(password)) {
        print("Invalid Input! Please try again: " , '\0');
    }

    print();
    try {
        if(uType == viewer) {
            userManager->createViewer(userName, nickName, password, dateObj);
            print("Success!");
        } else if(uType == streamer) {
            userManager->createStreamer(userName, nickName, password,dateObj);
            print("Success!");
        } else if(uType == admin){
            userManager->createAdmin(userName, nickName, password,dateObj);
            print("Success!");
        } else {
            print("Operation failed: ");
        }

    } catch (RestrictedAgeException &ex) {
        print("Operation failed: ");
        print(ex);
    } catch (InvalidPassword &ex) {
        print("Operation failed: ");
        print("An invalid password was used.");
    } catch (AlreadyExists<std::string> &e) {
        print("Operation failed: ");
        print(e);
    }

    waitForKey();
}

void StreamZ::recoverAccount() {
    std::string name;
    std::string password;
    print("Nick Name: ", '\0');

    while(!checkInput(name)) {
        print("Invalid Input! Please try again: " , '\0');
    }

    User * user = nullptr;

    try {
        user = searchManager->getUser(name);
        if(user->getUserType() != streamer || dynamic_cast<Streamer *>(user)->isActive())
        {
            print("That streamer's account is not disabled. Login in the appropriate menu.");
            waitForKey();
            return;
        }
    } catch (DoesNotExist<std::string> &ex) {
        print();
        print("That user does not exist.");

        waitForKey();

        return;
    }

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

    auto * str = dynamic_cast<Streamer *>(user);

    str->reenableAccount();

    print("Your account was reactivated successfully!");

    if(str->getStatus() == 1)
        print("You will receive 50 likes on your next stream as a welcome back gift...");

    print(LINE_BREAK);
    waitForKey();
}

void StreamZ::backupData(std::string fileName) {

    std::ofstream ff("../users_" + fileName, std::ofstream::trunc);

    if (!ff.is_open()){
        ff.open("users_" + fileName, std::ofstream::trunc);
        if(!ff.is_open()) throw "No file";
    }

    for (const auto & userPair : getDatabase().getUsers()){
        ff << userPair.second->getUserType() << " : ";
        userPair.second->writeToFile(ff);
    }
    for (const auto & streamer : getDatabase().getStreamers()){
        ff << streamer->getUserType() << " : ";
        streamer->writeToFile(ff);
    }
    ff.close();


    ff.open("../streams_" + fileName, std::ofstream::trunc);
    if (!ff.is_open()){
        ff.open("streams_" + fileName, std::ofstream::trunc);
        if(!ff.is_open()) throw "No file";
    }

    ff << LiveStream::lastId << std::endl;

    for (const auto & strPair : getDatabase().getStreams()){
        ff << strPair.second->getStreamFileType() << " : ";
        strPair.second->writeToFile(ff);
    }
    ff.close();



    ff.open("../donation_" + fileName, std::ofstream::trunc);
    if (!ff.is_open()){
        ff.open("donation_" + fileName, std::ofstream::trunc);
        if(!ff.is_open()) throw "No file";
    }

    BSTItrPre<DonationItem> it(getDatabase().donations);
    while (!it.isAtEnd())
    {
        ff << it.retrieve().getStreamerNick() << " : " << it.retrieve().getAmount() << " : " << it.retrieve().getEvaluation() << std::endl;
        it.advance();
    }
    ff.close();

    ff.open("../orders_" + fileName, std::ofstream::trunc);
    if(!ff.is_open()) {
        ff.open("orders_" + fileName, std::ofstream::trunc);
        if(!ff.is_open()) throw "No file";
    }

    ff << getUserM()->getOrdersSize() << std::endl;

    for (const auto & streamer : getDatabase().getStreamers()) {
        dynamic_cast<Streamer*>(streamer)->writeOrders(ff);
    }


    ff.close();
}

void StreamZ::readFromFile(std::string fileName) {
    std::ifstream ff;
    ff.open("../users_" + fileName);

    if (!ff.is_open()){
        ff.open("users_" + fileName);
        if(!ff.is_open()) throw "No file";
    }

    int uType;
    char sep;
    while (ff.peek() != EOF){

        ff >> uType >> sep;

        if(ff.eof()) break;

        User * newUser;

        switch ((userType) uType ) {

            case viewer:
                newUser = new Viewer();
                break;
            case streamer:
                newUser = new Streamer();
                break;
            case admin:
                newUser = new Admin();
                break;
        }

        newUser->readFromFile(ff);
        newUser->setStreamZ(this);

        if(newUser->getUserType() == streamer){
            dataBase.getStreamers().insert(newUser);
            //((Streamer*)newUser)->reenableAccount();
            //((Streamer*)newUser)->status = 0;
        }
        else
            dataBase.getUsers().insert(std::pair<std::string, User *>( newUser->getNickName(), newUser ));
    }

    ff.close();

    ff.open("../streams_" + fileName);

    if (!ff.is_open()){
        ff.open("streams_" + fileName);
        if(!ff.is_open()) throw "No file";
    }

    ff >> LiveStream::lastId;

    int sType;


    while (ff.peek() != EOF){

        ff >> sType >> sep;

        if(ff.eof()) break;

        Stream * newStream;

        switch ((streamFileType) sType ) {

            case finishedFile:
                newStream = new FinishedStream();
                break;
            case publicFile:
                newStream = new PublicStream();
                break;
            case privateFile:
                newStream = new PrivateStream();
                break;
        }

        newStream->readFromFile(ff);
        newStream->setStreamZ(this);
        dataBase.getStreams().insert(std::pair<ID, Stream *>( newStream->getStreamId(), newStream ));
    }

    ff.close();


    ff.open("../donation_" + fileName);

    if (!ff.is_open()){
        ff.open("donation_" + fileName);
        if(!ff.is_open()) throw "No file";
    }

    while (ff.peek() != EOF){

        if(ff.eof()) break;
        std::string  nick;
        unsigned amount, evaluation;
        char trash;
        ff >> nick >> trash >> amount >> trash >> evaluation;

        DonationItem newDonation(nick,amount,evaluation);

        dataBase.donations.insert(newDonation);
    }

    ff.close();

    ff.open("../orders_" + fileName);

    if (!ff.is_open()){
        ff.open("orders_" + fileName);
        if(!ff.is_open()) throw "No file";
    }

    unsigned max;

    ff >> max;
    std::cout << max << std::endl;

    getUserM()->setOrdersSize(max);

    Streamer * streamer;
    while (ff.peek() != EOF){
        if(ff.eof()) break;
        std::string  streamerNick, viewerNick;
        unsigned amount, availability;
        char trash;
        ff >> streamerNick >> trash;

        if(ff.eof()) break;

        streamer = dynamic_cast<Streamer *>(getSearchM()->getUser(streamerNick));
        while(trash != '/') {
            ff >> viewerNick >> trash >> amount >> trash >> availability >> trash;
            streamer->addOrder(viewerNick, amount, availability);
        }
    }

    ff.close();
}

void StreamZ::resetDatabase() {



}
