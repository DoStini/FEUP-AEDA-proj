//
// Created by andre on 10/17/2020.
//

#include "Date.h"

Date::Date(const std::string &date) {
    dateStruct = {};
    std::stringstream dateStream(date);
    const char* formats[3] = {"%Y/%m/%d", "%Y-%m-%d", "%Y %m %d"};

    for(short i = 0 ; i < 3; i++) {
        setToZero();
        dateStream >> std::get_time(&dateStruct, formats[i]);

        if(!dateStream.fail()) {
            if(checkValidDate()) return;

            throw InvalidDate();
        }

        dateStream = std::stringstream(date);
    }

    throw BadDateFormat(date);
}

Date::Date(int year, int month, int day) {
    setToZero();
    dateStruct.tm_year = year - 1900;
    dateStruct.tm_mon = month - 1;
    dateStruct.tm_mday = day;

    if(!checkValidDate()) throw InvalidDate();
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

int Date::getYearDifference(const Date &otherDate) const {
    const Date * maxDate = nullptr, *minDate = nullptr;

    if((*this) < otherDate) {
        maxDate = &otherDate;
        minDate = this;
    } else {
        maxDate = this;
        minDate = &otherDate;
    }

    int yearDiff = maxDate->dateStruct.tm_year - minDate->dateStruct.tm_year;

    if(maxDate->dateStruct.tm_mon >= minDate->dateStruct.tm_mon &&
       maxDate->dateStruct.tm_mday >= minDate->dateStruct.tm_mday) {
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
    if(result < 0) return false;
    else if(copy.tm_year != dateStruct.tm_year || copy.tm_mday != dateStruct.tm_mday || copy.tm_mon != dateStruct.tm_mon)
        return false;

    return true;
}

void Date::setToZero() {
    dateStruct = {};
}

inline bool operator <(const Date & lhs,const Date &rhs) {
    std::tm tmLhs = lhs.getTimeStruct(); std::tm tmRhs = rhs.getTimeStruct();
    time_t tLhs = mktime(&tmLhs), tRhs = mktime(&tmRhs);

    return difftime(tLhs, tRhs) < 0;
}

inline bool operator > (const Date &lhs, const Date &rhs) { return rhs < lhs; };
inline bool operator <= (const Date &lhs, const Date &rhs) { return !(lhs > rhs);};
inline bool operator >= (const Date &lhs, const Date &rhs) { return !(rhs > lhs);};
