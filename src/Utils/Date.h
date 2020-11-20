//
// Created by Nuno Alves on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_DATE_H
#define FEUP_AEDA_PROJ_DATE_H

#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <locale>
#include <ios>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "BadDateFormat.h"
#include "InvalidDate.h"
#include <cstdio>

constexpr static const uint16_t month_to_days[13] = {
        0, 31,28,31,30,31,30,31,31,30,31,30,31
};


/**
 * Class that stores a date in a simple, straightforward way.
 * @author Nuno Alves
 */
class Date {
public:

    /**
     * Constructor for date. Uses a string with a date to initialize.
     * @param date - String with a date
     * @param reversed - Indicates if the date is read from a reversed format
     * @throws BadDateFormat when using a bad date format
     * @throws InvalidDate when using an invalid date
     */
    explicit Date(const std::string &date, bool reversed = false);
    /**
     * Constructor for Date. If empty, sets the date to the current system date.
     *
     * @param year - Year
     * @param month - Month
     * @param day - Day of the month
     * @param hour - Hour
     * @param minute - Minute
     *
     * @throws InvalidDate when using an invalid date
     */
    explicit Date(int year, int month, int day, int hour = 0, int minute = 0);
    /**
     * Constructor for Date. Sets date values to system date.
     */
    explicit Date();
    /// Set date to the current system date
    void setSystemDate();
    /// @return The day of the month stored
    int getDay() const;
    /// @return The month stored
    int getMonth() const;
    /// @return The year stored
    int getYear() const;
    /// @return The year stored
    int getMinute() const;
    /// @return The hour stored
    int getHour() const;
    /// @return A string representing the date with the format "DD/MM/YYYY"
    std::string getStringDate() const;
    /// @return A string representing the date with the format "DD/MM/YYYY HH:MM"
    std::string getStringDateTime() const;
    /**
     * Gets the difference of years between two dates.
     * @param otherDate - the other date to be compared
     * @return returns an int32 of the difference in years.
     */
    int getYearDifference(const Date &otherDate) const;

    /**
     * Gets the tm struct.
     *
     * @return returns the tm struct dateStruct.
     */
    std::tm getTimeStruct() const;

    Date operator+(const std::tm &rhs) const;

    bool operator==(const Date &rhs) const;

    bool operator<(const Date &rhs) const;

    bool operator>(const Date &rhs) const;

    bool operator<=(const Date &rhs) const;

    bool operator>=(const Date &rhs) const;
private:

    std::tm dateStruct;
    /// Sets all date values to zero.
    void setToZero();
    /**
     * Checks if the date is valid.
     * @return returns true if valid, false if invalid
     */
    bool checkValidDate();

    /**
     * Checks if year (after 1900) is a leap year
     * @return true if leap-year
     */
    bool isLeapYear() const;
};


#endif //FEUP_AEDA_PROJ_DATE_H
