//
// Created by Nuno Alves on 10/17/2020.
//

#include "Date.h"
#include "unordered_map"


Date::Date(const std::string &date, bool reversed) {

    dateStruct = {0};
    std::stringstream dateStream(date);
    const char* formatsY[5] = {"%Y/%m/%d %H:%M\0",
                               "%Y/%m/%d %H\0",
                               "%Y/%m/%d\0",
                               "%Y-%m-%d\0",
                               "%Y %m %d\0"};
    const char* formatsD[2] = {
            "%d/%m/%Y %H:%M\0",
            "%d/%m/%Y\0"};
    const char ** formats = reversed ? formatsD : formatsY;
    size_t size = reversed? 2 : 5;

    for(size_t i = 0; i < size; i++) {
        setToZero();
        dateStream >> std::get_time(&dateStruct, formats[i]);

        if(!dateStream.fail()) {
            if(checkValidDate()) {
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

    if(maxDate->dateStruct.tm_mon < minDate->dateStruct.tm_mon) {
        yearDiff--;
    } else if(maxDate->dateStruct.tm_mon == minDate->dateStruct.tm_mon) {
        if(maxDate->dateStruct.tm_mday < minDate->dateStruct.tm_mday) yearDiff--;
    }

    return yearDiff;
}

void Date::setSystemDate() {
    time_t now = time(nullptr);
    dateStruct = *localtime(&now);
}

bool Date::checkValidDate() {
    int year = getYear(), month = getMonth(), day = getDay();

    if(day < 0) return false;
    if(month < 0 || month > 12) return false;
    if(year < 0) return false;
    if(month == 2) {
        if(isLeapYear() && day > 29) return false;
        if(day > 28) return false;
    }
    if(month > month_to_days[month]) return false;

    return true;
}

void Date::setToZero() {
    dateStruct = {0};
}

bool Date::operator==(const Date &rhs) const {
    std::tm tmLhs = getTimeStruct(); std::tm tmRhs = rhs.getTimeStruct();

    if(tmLhs.tm_year == tmRhs.tm_year && tmLhs.tm_mon == tmRhs.tm_mon && tmLhs.tm_mday == tmRhs.tm_mday
                                                                           && tmLhs.tm_hour == tmRhs.tm_hour
                                                                              && tmLhs.tm_min == tmRhs.tm_min)
        return true;

    return false;
}

bool Date::operator<(const Date &rhs) const {
    std::tm tmLhs = getTimeStruct(); std::tm tmRhs = rhs.getTimeStruct();

    if(tmLhs.tm_year < tmRhs.tm_year) return true;
    else if(tmLhs.tm_year == tmRhs.tm_year){
        if(tmLhs.tm_mon < tmRhs.tm_mon) return true;
        else if(tmLhs.tm_mon == tmRhs.tm_mon) {
            if(tmLhs.tm_mday < tmRhs.tm_mday) return true;
            else if(tmLhs.tm_mday == tmRhs.tm_mday) {
                if(tmLhs.tm_hour < tmRhs.tm_hour) return true;
                else if(tmLhs.tm_hour == tmRhs.tm_hour) {
                    if(tmLhs.tm_min < tmRhs.tm_min) return true;
                }
            }
        }
    }

    return false;
}

bool Date::operator>(const Date &rhs) const {
    return rhs < *this;
}

bool Date::operator<=(const Date &rhs) const {
    return !(rhs < *this);
}

bool Date::operator>=(const Date &rhs) const {
    return !(*this < rhs);
}

Date Date::operator+(const std::tm &rhs) const {
    Date result = *this;
    int div;

    result.dateStruct.tm_min += rhs.tm_min;
    div = result.dateStruct.tm_min / 60; result.dateStruct.tm_min %= 60;
    result.dateStruct.tm_hour += rhs.tm_hour + div;
    div = result.dateStruct.tm_hour / 24; result.dateStruct.tm_hour %= 24;
    result.dateStruct.tm_mday += rhs.tm_mday + div;

    while(result.dateStruct.tm_mday > month_to_days[result.dateStruct.tm_mon + 1]) {
        if(result.dateStruct.tm_mon == 1) {
            if(isLeapYear()) {
                if(result.dateStruct.tm_mday > 29) {
                    result.dateStruct.tm_mday -= 29; continue;
                } else break;
            }
        }

        result.dateStruct.tm_mday -= month_to_days[result.dateStruct.tm_mon];
    }


    return result;
}

bool Date::isLeapYear() const {
    int year = getYear();
    return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
}
