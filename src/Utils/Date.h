//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_DATE_H
#define FEUP_AEDA_PROJ_DATE_H

/**
 * Date class
 */
class Date {
public:
    /**
     * Constructor for Date. If empty, sets an invalid date -1/-1/-1
     *
     * @param d - Day of month
     * @param m - Month
     * @param y - Year
     */
    explicit Date(int d = -1, int m = -1, int y = -1);
    /// Set date to the current system date
    void setSystemDate();
    /// @return The day of the month stored
    int getDay() const;
    /// @return The month stored
    int getMonth() const;
    /// @return The year stored
    int getYear() const;
private:
    int day, month, year;
};


#endif //FEUP_AEDA_PROJ_DATE_H
