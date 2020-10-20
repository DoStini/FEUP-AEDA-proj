//
// Created by andre on 10/17/2020.
//

#include "Stream.h"
#include <utility>

Stream::Stream(std::string title, std::string language, unsigned int minAge) :
            title(std::move(title)), streamLanguage(std::move(language)), minAge(std::move(minAge)) {
    Date currDate; currDate.setSystemDate();
    beginDate = currDate;
    viewersNumber = 0;
    liveStream = true;
}