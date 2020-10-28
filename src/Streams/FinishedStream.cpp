//
// Created by adbp on 26/10/2020.
//

#include "FinishedStream.h"

#include <utility>


FinishedStream::FinishedStream(std::string title, languages language, genres genre, int numViewers, std::string streamerName)
                                : Stream(std::move(title),std::move(language),genre), numViewers(numViewers), streamerName(std::move(streamerName)) {

}

std::string FinishedStream::getInfo() const {
    return "Finished stream";
}

streamType FinishedStream::getStreamType() const {
    return finishedType;
}