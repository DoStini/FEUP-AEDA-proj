//
// Created by Nuno Alves on 28/10/2020.
//

#include "AdminAcc.h"
#include "Account.h"
#include "Admin.h"
#include "StreamZ.h"

AdminAcc::AdminAcc(User *admin, StreamZ * streamZ) : Account(admin, streamZ){
    if(Admin * ad = dynamic_cast<Admin*>(admin)) {
        this->admin = ad;
    } else {
        throw WrongUserTypeException(userType::admin);
    }

    options.insert(options.begin()+3, {
        std::bind(&AdminAcc::statistics, this),
        std::bind(&AdminAcc::removeUser, this),
        std::bind(&AdminAcc::removeStream, this)
    });
    optionDescriptions.insert(optionDescriptions.begin()+3, {
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
            "Most viewed type of stream.",
            "Most viewed genre of stream.",
            "Most viewed language.",
            "Most viewed streamer."
    };
    print();

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

    sOptions[option]();
}

void AdminAcc::numStreams() {
    print("The number of streams currently airing is: ",'\0');
    print(streamZ->getAdminOps()->numStreams());
}

void AdminAcc::numStreamsAll()  {
    print("The number of all streams created is: ",'\0');
    print(streamZ->getAdminOps()->numStreamsAll());
}

void AdminAcc::viewsPerStream() {
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
}
