//
// Created by Nuno Alves on 19/10/2020.
//

#ifndef FEUP_AEDA_PROJ_BADDATEFORMAT_H
#define FEUP_AEDA_PROJ_BADDATEFORMAT_H

#include <ostream>
#include <exception>

/**
 * Exception to be thrown when using a bad time format while trying to create a date class
 */
class BadDateFormat : public std::exception{
public:
    /**
     * Exception constructor´
     * @param date The string that tried to be converted to a date object
     */
    explicit BadDateFormat(const std::string &date);
    /**
     * Brief info about exception
     * @return
     */
    const char * what () const noexcept override;
    friend std::ostream &operator<<(std::ostream &os, const BadDateFormat &exception);

private:
    std::string date;
};



#endif //FEUP_AEDA_PROJ_BADDATEFORMAT_H
