//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_DATE_H
#define FEUP_AEDA_PROJ_DATE_H

#include <string>
#include <ctime>
#include <iomanip>
#include <locale>
#include <ios>
#include <sstream>
#include "date/BadDateFormat.h"

/**
 * Date class
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
     * Constructor for Date. If empty, sets an invalid date -1/-1/-1
     *
     * @param year - Year
     * @param month - Month
     * @param day - Day of the month
     */
    explicit Date(int year = -1, int month = -1, int day = -1);
    /// Set date to the current system date
    void setSystemDate();
    /// @return The day of the month stored
    int getDay() const;
    /// @return The month stored
    int getMonth() const;
    /// @return The year stored
    int getYear() const;
private:
    tm dateStruct;
};


#endif //FEUP_AEDA_PROJ_DATE_H
