//
// Created by andre on 10/17/2020.
//

#include "Date.h"

Date::Date(const std::string &date) {
    std::ios_base::iostate err = std::ios_base::goodbit;
    std::istringstream dateStream(date);

    std::use_facet<std::time_get<char>>(
            dateStream.getloc()).get_date({dateStream}, {}, dateStream, err, &dateStruct);

    dateStream.setstate(err);
    if(!dateStream.good()) {
        throw BadDateFormat(date);
    }
}

Date::Date(int year, int month, int day) {
    dateStruct.tm_year = year;
    dateStruct.tm_mon = month;
    dateStruct.tm_mday = day;
}

int Date::getDay() const {
    return dateStruct.tm_mday;
}

int Date::getMonth() const {
    return dateStruct.tm_mon;
}

int Date::getYear() const {
    return dateStruct.tm_year;
}

void Date::setSystemDate() {
    time_t now = time(0);
    dateStruct = *localtime(&now);
}
