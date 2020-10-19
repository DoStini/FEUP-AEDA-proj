//
// Created by andre on 10/17/2020.
//

#include "Date.h"

Date::Date(const std::string &date) {
    std::stringstream dateStream(date);
    const char* formats[3] = {"%Y/%m/%d", "%Y-%m-%d", "%Y%t%m%t%d"};

    for(short int i = 0; i < 3; i++) {
        setToZero();
        dateStream >> std::get_time(&dateStruct, formats[i]);

        if(!dateStream.fail()) return;
    }

    throw BadDateFormat(date);
}

Date::Date(int year, int month, int day) {
    setToZero();
    dateStruct.tm_year = year - 1900;
    dateStruct.tm_mon = month - 1;
    dateStruct.tm_mday = day;
}

Date::Date() {
    setSystemDate();
}

int Date::getDay() const {
    return dateStruct.tm_mday;
}

int Date::getMonth() const {
    return dateStruct.tm_mon + 1;
}

int Date::getYear() const {
    return dateStruct.tm_year + 1900;
}

void Date::setSystemDate() {
    time_t now = time(0);
    dateStruct = *localtime(&now);
}

void Date::setToZero() {
    dateStruct = {};
}
