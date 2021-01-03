//
// Created by Nuno Alves on 28/10/2020.
//

#include "AdminAcc.h"
#include "Admin.h"
#include "StreamZ.h"
#include "EmptyDatabaseException.h"

AdminAcc::AdminAcc(User *admin, StreamZ * streamZ) : Account(admin, streamZ){
    if(auto * ad = dynamic_cast<Admin*>(admin)) {
        this->admin = ad;
    } else {
        throw WrongUserTypeException(userType::admin);
    }

    options.insert(options.begin()+5, {
        [this] { statistics(); },
        [this] { removeUser(); },
        [this] { removeStream(); },
        [this] { changeMaxOrders();},
        [this] { displayMaxOrders(); },
        [this] { removeDonation(); },
        [this] { listDonations(); }
    });
    optionDescriptions.insert(optionDescriptions.begin()+5, {
        "Display the statistics panel.",
        "Delete a user from the platform.",
        "Delete a stream from the platform.",
        "Change the maximum number of orders per streamer.",
        "Display the maximum number of orders per streamer.",
        "Delete a donation from the platform.",
        "List donations of platform."
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
    std::stringstream ss;
    print("STATISTICS: ");
    std::vector<Option> sOptions = {
            [](){},
            [this] { numStreams(); },
            [this] { numStreamsAll(); },
            [this] { numStreamsType(); },
            [this] { viewsPerStream(); },
            [this] { mostViewedType(); },
            [this] { mostViewedGenre(); },
            [this] { mostViewedLanguage(); },
            [this] { mostViewedStreamer(); }
    };
    std::vector<std::string> descriptions = {
            "Exit statistics panel",
            "Number of streams currently airing.",
            "Number of all streams ever aired.",
            "Number of streams of a certain type in a certain time interval.",
            "Mean views per stream during a certain time interval.",
            "Most/Least viewed type of stream.",
            "Most/Least viewed genre of stream.",
            "Most/Least viewed language.",
            "Most viewed streamer."
    };
    print();

    do {
        for(unsigned i = 0; i < sOptions.size(); i++) {
            ss.str("");

            ss << i << ". " << descriptions[i];
            print(ss.str());
        }

        print();
        print("Choose an option: ", '\0');

        while (!checkInput(option) || option < 0 || option >= sOptions.size()) {
            print("Invalid Option! Please try again: " , '\0');
        }
        if(option == 0) break;

        print(LINE_BREAK);
        sOptions[option]();
        print(LINE_BREAK);
    } while(option != 0);
}

void AdminAcc::numStreams() {
    print("The number of streams currently airing is: ",'\0');
    print(streamZ->getAdminOps()->numStreams());

    print();
    waitForKey();
}

void AdminAcc::numStreamsAll()  {
    print("The number of all streams created is: ",'\0');
    print(streamZ->getAdminOps()->numStreamsAll());

    print();
    waitForKey();
}

void AdminAcc::viewsPerStream() {
    std::pair<Date, Date> dateInterval;
    bool validInterval = getTimeInterval(dateInterval);
    float views;

    print();
    if(validInterval) {
        print("Mean views per stream between dates ",'\0');
        print(dateInterval.first.getStringDate(),'\0');
        print(" and ", '\0');
        print(dateInterval.second.getStringDate(),'\0');
        print(": ");

        views = streamZ->getAdminOps()->medianViewsStream(dateInterval.first, dateInterval.second);
    } else {
        print("Mean views per stream: ", '\0');

        views = streamZ->getAdminOps()->medianViewsStream();
    }

    print();
    print(views);
    print();

    waitForKey();
}

void AdminAcc::numStreamsType() {
    print("What is the type of stream you wish to know the quantity of?");
    print();
    print("1. Public");
    print("2. Private");
    print();
    uint16_t option;

    while(!checkInput(option) || option <1 || option > 2) {
        print("Invalid Input! Please try again: ", '\0');
    }

    print();
    std::pair<Date, Date> dateInterval;
    bool validInterval = getTimeInterval(dateInterval);
    long num;

    print();

    if(validInterval) {
        print("Number of streams of that type between dates ",'\0');
        print(dateInterval.first.getStringDate(),'\0');
        print(" and ", '\0');
        print(dateInterval.second.getStringDate(),'\0');
        print(": ");

        num = streamZ->getAdminOps()->numStreams((streamType) option, dateInterval.first, dateInterval.second);
    } else {
        print("Number of streams of that type: ", '\0');

        num = streamZ->getAdminOps()->numStreams((streamType) option);
    }

    print();
    print(num);
    print();

    waitForKey();
}

bool AdminAcc::getTimeInterval(std::pair<Date, Date> &dateInterval) {
    std::string date;

    do {
        try {
            print("What is the date of the first interval limit? (0 for no interval)");
            print("(Format: YYYY/MM/DD or YYYY-MM-DD or YYYY MM DD) ", '\0');

            getString(date);

            if(date == "0") {
                return false;
            }

            dateInterval.first = Date(date);

            print("What is the date of the second interval limit? (0 for no interval)");
            print("(Format: YYYY/MM/DD or YYYY-MM-DD or YYYY MM DD) ", '\0');

            getString(date);

            if(date == "0") {
                return false;
            }

            dateInterval.second = Date(date);

            break;
        } catch (BadDateFormat &ex) {
            print("Date was in a wrong format. Please try again: ");
        } catch (InvalidDate &ex) {
            print("Date is not valid! Please try again: ");
        }
    } while(true);


    return true;
}

void AdminAcc::mostViewedType() {
    try {
        streamType type = streamZ->getAdminOps()->rankViewsTypes();

        print("The most viewed type of stream is: ");
        if(type == publicType) print("Public");
        else print("Private");

        type = streamZ->getAdminOps()->rankViewsTypes(true);

        print("The least viewed type of stream is: ");
        if(type == publicType) print("Public");
        else print("Private");
    } catch (EmptyDatabaseException &e) {
        print("Operation failed: ");
        print(e);
    }

    print();
    waitForKey();
}

void AdminAcc::mostViewedStreamer() {
    try {
        Streamer * streamer = streamZ->getAdminOps()->mostViewed();

        print("The most viewed streamer is: ");
        print(streamer->getShortDescription());
    } catch (EmptyDatabaseException &e) {
        print("Operation failed: ");
        print(e);
    }

    print();
    waitForKey();
}

void AdminAcc::mostViewedGenre() {
    try {
        genre gnr = streamZ->getAdminOps()->rankViewsGenres();

        print("The most viewed genre is: ");
        print(genreTypes[(int)gnr]);

        gnr = streamZ->getAdminOps()->rankViewsGenres(true);

        print("The least viewed genre is: ");
        print(genreTypes[(int)gnr]);
    } catch (EmptyDatabaseException &e) {
        print("Operation failed: ");
        print(e);
    }

    print();
    waitForKey();
}

void AdminAcc::mostViewedLanguage() {
    try {
        language lng = streamZ->getAdminOps()->rankViewsLang();

        print("The most viewed language is: ");
        print(languageTypes[(int)lng]);

        lng = streamZ->getAdminOps()->rankViewsLang(true);

        print("The least viewed language is: ");
        print(languageTypes[(int)lng]);
    } catch (EmptyDatabaseException &e) {
        print("Operation failed: ");
        print(e);
    }

    print();
    waitForKey();
}

void AdminAcc::changeMaxOrders() {
    int num;

    print("What is the new max size of orders per streamer? (0 to leave unchanged) ", '\0');

    while (!checkInput(num) || num < 0) {
        print("Invalid input! Please try again: ", '\0');
    }

    if (num > 0) streamZ->getAdminOps()->changeMaxOrdersSize(num);

    print();
    print("Operation Success!");
    waitForKey();
}

void AdminAcc::removeDonation() {
    std::string nickName;
    int amount, evaluation;

    print("What is the nickname of the streamer you wish to remove donation? (empty to cancel) ", '\0');

    getTruncatedString(nickName);

    print();
    if(nickName.empty()) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }

    print("What is the amount of money to remove donation? ", '\0');

    while (!checkInput(amount)) {
        print("Invalid input! Please try again: ", '\0');
    }


    print("What is the evaluation? ", '\0');

    while (!checkInput(evaluation)) {
        print("Invalid input! Please try again: ", '\0');
    }

    try {
        streamZ->getDonationManager()->deleteDonation(nickName,amount,evaluation);

        print("Operation success!");

    } catch (AlreadyExists<DonationItem> &e) {
        print("Operation failed: ");
        print(e);
    } catch (DoesNotExist<DonationItem> &e) {
        print("Operation failed: ");
        print("No such donation.");
    } catch (NotInRangeValue &e) {
        print("Operation failed: ");
        print(e);
    }

    waitForKey();
}

void AdminAcc::listDonations() {

    std::vector<Donation*> donations;
    std::stringstream ss;


    std::vector<std::string> streamerNicks;
    vector<unsigned int> evaluations;
    unsigned int eval;
    std::string streamer;
    unsigned minAmount;
    unsigned maxAmount;

    do {
        print("Stream Nick (empty for all streams/to stop): ", '\0');
        getString(streamer);
        if(!streamer.empty()) {
            streamerNicks.push_back(streamer);
        }
    } while(!streamer.empty());



    do {
        print("Chose evaluations from 1 to 5 (0 to stop, empty for all)");
        while(!checkInput(eval)) {
            print("Invalid Input! Please try again: ", '\0');
        }
        if(eval >= 1 && eval <= 5) {
            evaluations.push_back(eval);
        }
    } while(eval != 0);


    print("Minimum donation amount: ", '\0');

    while(!checkInput(minAmount)) {
        print("Invalid Input! Please try again: ", '\0');
    }


    print("Maximum donation amount: ", '\0');

    while(!checkInput(maxAmount)) {
        print("Invalid Input! Please try again: ", '\0');
    }



    streamZ->getSearchM()->listDonations(donations,streamerNicks,minAmount,maxAmount,evaluations);

    print();
    if(donations.empty()) {
        print("There are no donations for the parameters selected.");
        waitForKey();
        return;
    }


    print("Here are all the donations: ");
    print();
    printPagedList(donations, std::function<std::string(Donation*)> ( [](Donation* donation){
        return donation->getShortDescription();
    }));

    print();
    waitForKey();

}

void AdminAcc::displayMaxOrders() {
    print("The max size of orders per streamer is ", '\0');
    print(streamZ->getAdminOps()->getMaxOrdersSize());

    print();
    waitForKey();
}
