//
// Created by Nuno Alves on 19/10/2020.
//

#ifndef FEUP_AEDA_PROJ_INVALIDDATE_H
#define FEUP_AEDA_PROJ_INVALIDDATE_H

#include <ostream>
#include <exception>

/**
 * Exception to be thrown when using an invalid date in the date class.
 */
class InvalidDate : public std::exception {
public:
    InvalidDate() = default;
    /**
     * Brief info about exception
     * @return
     */
    const char * what () const noexcept override;
    friend std::ostream &operator<<(std::ostream &os, const InvalidDate &exception);
};


#endif //FEUP_AEDA_PROJ_INVALIDDATE_H
