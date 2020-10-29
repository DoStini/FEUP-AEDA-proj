//
// Created by Nuno Alves on 29/10/2020.
//

#ifndef FEUP_AEDA_PROJ_INVALIDPASSWORD_H
#define FEUP_AEDA_PROJ_INVALIDPASSWORD_H


#include <exception>
#include <string>
#include <ostream>

/**
 * Exception to be thrown when someone tries to register underage user
 */
class InvalidPassword : public std::exception{
public:
    InvalidPassword() = default;
    /**
     * Brief info about exception
     * @return
     */
    const char * what () const noexcept override;
};


#endif //FEUP_AEDA_PROJ_INVALIDPASSWORD_H
