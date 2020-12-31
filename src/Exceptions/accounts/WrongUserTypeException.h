//
// Created by Nuno Alves on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_WRONGUSERTYPEEXCEPTION_H
#define FEUP_AEDA_PROJ_WRONGUSERTYPEEXCEPTION_H

#include <ostream>
#include <exception>
#include "User.h"

/**
 * Exception to be thrown when creating an account with the wrong user type
 */
class WrongUserTypeException : public std::exception{
public:
    WrongUserTypeException(userType type);
    /**
     * Brief info about exception
     * @return
     */
    const char * what () const noexcept override;
    friend std::ostream &operator<<(std::ostream &os, const WrongUserTypeException &exception);
private:
    userType type;
};


#endif //FEUP_AEDA_PROJ_WRONGUSERTYPEEXCEPTION_H
