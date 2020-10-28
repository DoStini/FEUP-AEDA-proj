//
// Created by adbp on 26/10/2020.
//

#include "FinishedStream.h"

#include <utility>


FinishedStream::FinishedStream(std::string title, language language, genre streamGenre, int numViewers, std::string streamerName)
                                : Stream(std::move(title),language,streamGenre), numViewers(numViewers), streamerName(std::move(streamerName)) {

}

std::string FinishedStream::getInfo() const {
    return "Finished stream";
}

streamType FinishedStream::getStreamType() const {
    return finishedType;
}