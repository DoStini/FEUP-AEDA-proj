//
// Created by Nuno Alves on 28/10/2020.
//

#include "StreamerAcc.h"
#include "Streamer.h"
#include "Account.h"
#include "StreamZ.h"
#include "NotInWhiteListException.h"

StreamerAcc::StreamerAcc(User *user, StreamZ * streamZ) : Account(user, streamZ){
    if(Streamer * streamer = dynamic_cast<Streamer*>(user)) {
        this->streamer = streamer;
    } else {
        throw WrongUserTypeException(userType::streamer);
    }

    options.insert(options.begin()+5, {
        std::bind(&StreamerAcc::startStream, this),
        std::bind(&StreamerAcc::checkNumViewers, this),
        std::bind(&StreamerAcc::kickUserFromStream, this),
        std::bind(&StreamerAcc::addUserToPrivate, this),
        std::bind(&StreamerAcc::removeUserFromPrivate, this),
        std::bind(&StreamerAcc::endStream, this)
    });
    optionChecks[5] = [this](){return !this->streamer->streaming();};
    optionChecks[6] = optionChecks[7] = optionChecks[10] = [this](){return this->streamer->streaming();};
    optionChecks[8] = optionChecks[9] = [this](){
        if(!this->streamer->streaming()) return false;

        ID streamID = this->streamer->getStreamID();
        return this->streamZ->getSearchM()->getStream(streamID)->getStreamType() == privateType;
    };
    optionDescriptions.insert(optionDescriptions.begin() + 5, {
        "Start a stream.",
        "Check the number of viewers on your stream.",
        "Kick viewer from the stream.",
        "Add user to stream whitelist.",
        "Remove user from stream whitelist.",
        "End stream."
    });
    nOptions = options.size();
}

void StreamerAcc::startStream() {
    uint16_t option;
    unsigned age;
    std::string streamName;
    genre genreT;
    language languageT;
    streamType streamTypeT;
    std::stringstream ss;

    print("Stream Name: ", '\0');

    getString(streamName);

    print("Available Stream Genres: ");
    print();

    for(uint32_t i = (unsigned int) genre::gaming; i != genre::LASTG; i++) {
        ss.str("");
        ss << i + 1 << ". " << genreTypes[i];

        print(ss.str());
    }

    print();
    print("Choose the genre: ", '\0');

    while(!checkInput(option) || option < 1 || option > LASTG) {
        print("Invalid input! Please try again: ", '\0');
    }

    genreT = (genre) (option - 1);

    print("Available Stream Languages: ");
    print();

    for(uint32_t i = (unsigned int) language::PT_PT; i != language::LASTL; i++) {
        ss.str("");
        ss << i + 1 << ". " << languageTypes[i];

        print(ss.str());
    }

    print();
    print("Choose the stream language: ", '\0');

    while(!checkInput(option) || option < 1 || option > LASTL) {
        print("Invalid input! Please try again: ", '\0');
    }

    languageT = (language) (option - 1);

    print("Available Stream types: ");
    print();

    print("1. Public");
    print("2. Private");

    print();
    print("Choose the stream type: ", '\0');

    while(!checkInput(option) || option < 1 || option > 2) {
        print("Invalid input! Please try again: ", '\0');
    }

    streamTypeT = (streamType) option;

    print("What is the minimum age of the stream? ", '\0');

    while(!checkInput(age) || age < VIEWER_MIN_AGE) {
        print("Invalid Age! Please try again: ", '\0');
    }
    unsigned maxViewers = MAX_VIEWERS;

    if(streamTypeT == privateType) {
        print("What is the maximum number of viewers that can watch the stream? ", '\0');

        while(!checkInput(maxViewers) || maxViewers < 0) {
            print("Invalid Number! Please try again: ", '\0');
        }
    }

    print();
    print("Starting Stream...");
    print();

    try {
        if(streamTypeT == publicType) {
            streamer->startPublicStream(streamName, languageT, genreT, age);
        } else {
            streamer->startPrivateStream(streamName, languageT, genreT, age, maxViewers);
        }

        print("Success!");
    } catch (AlreadyInStreamException &e) {
        print("Operation failed: ");
        print(e);
    }

    waitForKey();
}

void StreamerAcc::checkNumViewers() {
    std::stringstream  ss;
    ID streamID;
    unsigned viewers;

    try {
        streamID = streamer->getStreamID();
        viewers = streamZ->getSearchM()->getStream(streamID)->getNumViewers();
    } catch (NotInStreamException &e) {
        print("Operation failed: ");
        print(e);
    }

    ss << viewers;

    if(viewers == 1) ss << " is";
    else ss << " are";

    ss << " watching your stream.";

    print(ss.str());

    waitForKey();
}

void StreamerAcc::kickUserFromStream() {
    std::string nickName;

    print("What is the nickname of the viewer you want to kick? (empty to cancel) ", '\0');

    getTruncatedString(nickName);

    print();
    if(nickName.empty()) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }

    try {
        streamer->kickUser(nickName);

        print("Operation success!");
    } catch (NotInStreamException &e) {
        print("Operation failed: ");
        print(e);
    } catch (DoesNotExist<std::string> &e) {
        print("Operation failed: ");
        print("No such user with the nickname ",'\0');
        print(nickName);
    }

    waitForKey();
}

void StreamerAcc::addUserToPrivate() {
    std::string nickName;
    ID streamID;

    if(!streamer->streaming()) {
        print("Operation cancelled: ");
        print("You are not streaming.");
    }

    print("What is the nickname of the viewer you want to add to your whitelist? (empty to cancel) ", '\0');

    getTruncatedString(nickName);

    print();
    if(nickName.empty()) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }

    try {
        streamID = streamer->getStreamID();
        PrivateStream * privateStream = dynamic_cast<PrivateStream *>(streamZ->getSearchM()->getStream(streamID));
        if(!privateStream) {
            throw NotPrivateStreamException(streamID);
        }

        privateStream->addValidUser(nickName);

        print("Operation success!");
    } catch (NotInStreamException &e) {
        print("Operation failed: ");
        print(e);
    } catch (DoesNotExist<ID> &e) {
        print("Operation failed: ");
        print("No such stream with ID ", '\0');
        print(streamID);
    } catch (DoesNotExist<std::string> &e) {
        print("Operation failed: ");
        print("No such user with nickname ", '\0');
        print(nickName);
    } catch (AlreadyInWhiteListException &e) {
        print("Operation failed: ");
        print(e);
    }

    waitForKey();
}

void StreamerAcc::endStream() {
    char option;
    print("Do you want to end your stream? (Y/N) ", '\0');

    while(!checkInput(option) || option != 'Y') {
        print("Invalid Option! Please try again: ", '\0');
    }

    print();
    try {
        streamer->closeStream();

        print("Operation success!");
    } catch (NotInStreamException &e) {
        print("Operation failed: ");
        print(e);
    }

    waitForKey();
}

void StreamerAcc::removeUserFromPrivate() {
    std::string nickName;
    ID streamID;

    print("What is the nickname of the viewer you want to remove from your whitelist? (empty to cancel) ", '\0');

    getTruncatedString(nickName);

    print();
    if(nickName.empty()) {
        print("Operation cancelled.");

        waitForKey();

        return;
    }

    try {
        streamID = streamer->getStreamID();
        PrivateStream * privateStream = dynamic_cast<PrivateStream *>(streamZ->getSearchM()->getStream(streamID));
        if(!privateStream) {
            throw NotPrivateStreamException(streamID);
        }

        privateStream->removeValidUser(nickName);

        print("Operation success!");
    } catch (NotInStreamException &e) {
        print("Operation failed: ");
        print(e);
    } catch (DoesNotExist<ID> &e) {
        print("Operation failed: ");
        print("No such stream with ID ", '\0');
        print(streamID);
    } catch (DoesNotExist<std::string> &e) {
        print("Operation failed: ");
        print("No such user with nickname ", '\0');
        print(nickName);
    } catch (NotInWhiteListException &e) {
        print("Operation failed: ");
        print(e);
    }

    waitForKey();
}
