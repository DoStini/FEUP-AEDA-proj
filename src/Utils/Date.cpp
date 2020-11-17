//
// Created by Nuno Alves on 10/17/2020.
//

#include "Date.h"

Date::Date(const std::string &date) {
    dateStruct = {0};
    std::stringstream dateStream(date);
    const char* formats[7] = {"%Y/%m/%d %H:%M\0",
                              "%d/%m/%Y %H:%M\0",
                              "%Y/%m/%d %H\0",
                              "%d/%m/%Y\0",
                              "%Y/%m/%d\0",
                              "%Y-%m-%d\0",
                              "%Y %m %d\0"};

    for(auto & format : formats) {
        setToZero();
        dateStream >> std::get_time(&dateStruct, format);

        if(!dateStream.fail()) {
            if(checkValidDate()) {
                fixDate();
                return;
            }
        }

        dateStream = std::stringstream(date);
    }

    throw BadDateFormat(date);
}

Date::Date(int year, int month, int day, int hour, int minute) {
    setToZero();
    dateStruct.tm_year = year - 1900;
    dateStruct.tm_mon = month - 1;
    dateStruct.tm_mday = day;
    dateStruct.tm_hour = hour;
    dateStruct.tm_min = minute;

    if(!checkValidDate()) throw InvalidDate();

    fixDate();
}

Date::Date() {
    setSystemDate();
}

std::tm Date::getTimeStruct() const {
    return dateStruct;
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

int Date::getHour() const {
    return dateStruct.tm_hour;
}

int Date::getMinute() const {
    return dateStruct.tm_min;
}

std::string Date::getStringDate() const {
    char buffer[12];

    strftime(buffer, 12, "%d/%m/%Y", &dateStruct);

    return std::string(buffer);
}

std::string Date::getStringDateTime() const {
    char buffer[18];

    strftime(buffer, 18, "%d/%m/%Y %H:%M", &dateStruct);

    return std::string(buffer);
}

int Date::getYearDifference(const Date &otherDate) const {
    const Date * maxDate = this,* minDate = &otherDate;

    int yearDiff = maxDate->dateStruct.tm_year - minDate->dateStruct.tm_year;

    if(maxDate->dateStruct.tm_mon >= minDate->dateStruct.tm_mon &&
       maxDate->dateStruct.tm_mday >= minDate->dateStruct.tm_mday &&
       maxDate->dateStruct.tm_hour >= minDate->dateStruct.tm_hour &&
       maxDate->dateStruct.tm_min >= minDate->dateStruct.tm_min) {
        return yearDiff;
    }

    return yearDiff - 1;
}

void Date::setSystemDate() {
    time_t now = time(nullptr);
    dateStruct = *localtime(&now);
}

bool Date::checkValidDate() {
    std::tm copy = dateStruct;

    time_t result = mktime(&copy);
    if(copy.tm_isdst) {
        dateStruct.tm_isdst = 1;

        copy = dateStruct;
        result = mktime(&copy);
    }
    if(result < 0) return false;
    else if(copy.tm_year != dateStruct.tm_year || copy.tm_mday != dateStruct.tm_mday ||
            copy.tm_mon != dateStruct.tm_mon || copy.tm_hour != dateStruct.tm_hour ||
            copy.tm_min != dateStruct.tm_min)
        return false;

    return true;
}

void Date::setToZero() {
    dateStruct = {0};
}

;
;
void Date::fixDate() {
    mktime(&dateStruct);
}


bool Date::operator<(const Date &rhs) const {
    std::tm tmLhs = getTimeStruct(); std::tm tmRhs = rhs.getTimeStruct();
    time_t tLhs = mktime(&tmLhs), tRhs = mktime(&tmRhs);

    return difftime(tLhs, tRhs) < 0;
}

bool Date::operator>(const Date &rhs) const {
    return rhs < *this;
}

bool Date::operator<=(const Date &rhs) const {
    return !(rhs < *this);
}

bool Date::operator>=(const Date &rhs) const {
    return !(*this < rhs);
};
