//
// Created by adbp on 02/11/2020.
//

#ifndef FEUP_AEDA_PROJ_ALREADYINWHITELISTEXCEPTION_H
#define FEUP_AEDA_PROJ_ALREADYINWHITELISTEXCEPTION_H

#include <exception>
#include <ostream>

#include "utils.h"

/**
 * Exception to be thrown when a user is already in the whitelist and tries to be added again
 */
class AlreadyInWhiteListException: public std::exception{
public:
    /**
     * Constructor
     * @param user - The user that originated the error
     * @param streamWhilisted - id of the streamer where de user is whitlisted
     */
    AlreadyInWhiteListException(std::string user, unsigned long long int streamWhilisted);

    /**
     * Brief info about exception
     * @return
     */
    const char * what() const noexcept override;

    friend std::ostream &operator<<(std::ostream &os, const AlreadyInWhiteListException &exception);

private:
    std::string user;
    unsigned long long int streamWhilisted;

};


#endif //FEUP_AEDA_PROJ_ALREADYINWHITELISTEXCEPTION_H
