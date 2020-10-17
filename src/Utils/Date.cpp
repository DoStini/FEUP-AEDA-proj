//
// Created by andre on 10/17/2020.
//

#include "Date.h"
#include <ctime>

Date::Date(int d, int m, int y) : day(d), month(m), year(y){}

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

void Date::setSystemDate() {

    time_t now = time(0);
    tm * currDate = localtime(&now);
    year = currDate->tm_year + 1900;
    month = currDate->tm_mon + 1;
    day = currDate->tm_mday;

}
