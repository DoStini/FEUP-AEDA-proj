//
// Created by andre on 10/17/2020.
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

/**
 * Class that stores a date in a simple, straightforward way.
 * @author Nuno Alves
 */
class Date {
public:

    /**
     * Constructor for date. Uses a string with a date to initialize.
     * @param date - String with a date
     * @throws BadDateFormat when using a bad date format
     */
    explicit Date(const std::string &date);
    /**
     * Constructor for Date. If empty, sets the date to the current system date.
     *
     * @param year - Year
     * @param month - Month
     * @param day - Day of the month
     */
    explicit Date(int year, int month, int day);
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
    /**
     * Gets the absolute difference of years between two dates.
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

    friend bool operator < (const Date &lhs, const Date &rhs);
    friend bool operator > (const Date &lhs, const Date &rhs);
    friend bool operator <= (const Date &lhs, const Date &rhs);
    friend bool operator >= (const Date &lhs, const Date &rhs);
private:
    std::tm dateStruct;
    /// Sets all date values to zero.
    void setToZero();
    /**
     * Checks if a date is valid
     * @return returns true if valid, false if invalid
     */
    bool checkValidDate() const;
};


#endif //FEUP_AEDA_PROJ_DATE_H
