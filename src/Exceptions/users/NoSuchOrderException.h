//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_NOSUCHORDEREXCEPTION_H
#define FEUP_AEDA_PROJ_NOSUCHORDEREXCEPTION_H

#include <exception>
#include <string>
#include <ostream>

/**
 * Exception to be thrown when someone tries to remove an order that does not exist.
 */
class NoSuchOrderException : public std::exception{
public:
    NoSuchOrderException(const std::string& name);
    /**
     * Brief info about exception
     * @return
     */
    const char * what () const noexcept override;
    friend std::ostream &operator<<(std::ostream &os, const NoSuchOrderException &exception);

private:
    std::string userName;
};


#endif
