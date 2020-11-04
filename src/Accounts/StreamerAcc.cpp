//
// Created by Nuno Alves on 28/10/2020.
//

#include "StreamerAcc.h"
#include "Streamer.h"
#include "Account.h"

StreamerAcc::StreamerAcc(User *user, StreamZ * streamZ) : Account(user, streamZ){
    if(Streamer * streamer = dynamic_cast<Streamer*>(user)) {
        this->streamer = streamer;
    } else {
        throw WrongUserTypeException(userType::streamer);
    }

    options.insert(options.begin()+3, {
        std::bind(&StreamerAcc::startStream, this)
    });
    optionChecks[3] = [this](){return this->streamer->getStreamID() == 0;};
    optionDescriptions.insert(optionDescriptions.begin() + 3, {
        "Start a stream."
    });
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
