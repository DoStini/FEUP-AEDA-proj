//
// Created by Nuno Alves on 28/10/2020.
//

#include "AdminAcc.h"
#include "Account.h"
#include "Admin.h"
#include "StreamZ.h"
#include "EmptyDatabaseException.h"

AdminAcc::AdminAcc(User *admin, StreamZ * streamZ) : Account(admin, streamZ){
    if(Admin * ad = dynamic_cast<Admin*>(admin)) {
        this->admin = ad;
    } else {
        throw WrongUserTypeException(userType::admin);
    }

    options.insert(options.begin()+5, {
        std::bind(&AdminAcc::statistics, this),
        std::bind(&AdminAcc::removeUser, this),
        std::bind(&AdminAcc::removeStream, this)
    });
    optionDescriptions.insert(optionDescriptions.begin()+5, {
        "Display the statistics panel.",
        "Delete a user from the platform.",
        "Delete a stream from the platform."
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
            std::bind(&AdminAcc::numStreams, this),
            std::bind(&AdminAcc::numStreamsAll, this),
            std::bind(&AdminAcc::numStreamsType, this),
            std::bind(&AdminAcc::viewsPerStream, this),
            std::bind(&AdminAcc::mostViewedType, this),
            std::bind(&AdminAcc::mostViewedGenre, this),
            std::bind(&AdminAcc::mostViewedLanguage, this),
            std::bind(&AdminAcc::mostViewedStreamer, this)
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
            "Most/Least viewed streamer."
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

// TODO THIS
void AdminAcc::numStreamsType() {

}

bool AdminAcc::getTimeInterval(std::pair<Date, Date> &dateInterval) {
    std::string date;

    do {
        try {
            print("What is the date of the first interval limit? (empty for no interval)");
            print("(Format: YYYY/MM/DD or YYYY-MM-DD or YYYY MM DD) ", '\0');

            getTruncatedString(date);

            if(date.empty()) {
                return false;
            }

            dateInterval.first = Date(date);

            print("What is the date of the second interval limit? (empty for no interval)");
            print("(Format: YYYY/MM/DD or YYYY-MM-DD or YYYY MM DD) ", '\0');

            getTruncatedString(date);

            if(date.empty()) {
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
    print("The most viewed type of stream is: ",'\0');


}

void AdminAcc::mostViewedStreamer() {
    try {
        Streamer * streamer = streamZ->getAdminOps()->mostViewed();

        print("The most viewed streamer is: ");
        print(streamer->getLongDescription());

        waitForKey();
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
