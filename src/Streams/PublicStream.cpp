//
// Created by adbp on 18/10/2020.
//

#include "PublicStream.h"

#include <utility>

PublicStream::PublicStream(std::string title, std::string language, unsigned minAge) : Stream(std::move(title), std::move(language), minAge) {}

std::string PublicStream::getInfo() const {
    return "Some public stream";
}
