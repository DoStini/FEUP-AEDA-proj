//
// Created by adbp on 26/10/2020.
//

#include "FinishedStream.h"

FinishedStream::FinishedStream(std::string title, std::string language, int numViewers, std::string streamerName)
                                :Stream(title,language), numViewers(numViewers), streamerName(streamerName) {

}

std::string FinishedStream::getInfo() const {
    return "Finished stream";
}