//
// Created by adbp on 21/12/2020.
//

#ifndef FEUP_AEDA_PROJ_NOTINRANGEVALUE_H
#define FEUP_AEDA_PROJ_NOTINRANGEVALUE_H

#include <exception>
#include <string>
#include <ostream>


/**
 * Class to be throw when some value is not supported by some parameter
 */
class NotInRangeValue : public std::exception {
public:
    /**
     * Exception constructor
     * @param value parameter and the given invalid number
     */
    explicit NotInRangeValue(const std::string parameter, unsigned number) : parameter(parameter), number(number) {};
    friend std::ostream &operator<<(std::ostream &os, const NotInRangeValue &outOfRange){
        os << outOfRange.parameter << " does not support the number " << outOfRange.number;
        return os;
    };
    const char * what() const noexcept override{
        return "Invalid value of parameter";
    };

private:
    std::string parameter; /// parameter invalid
    unsigned number; /// invalid number
};


#endif //FEUP_AEDA_PROJ_NOTINRANGEVALUE_H
