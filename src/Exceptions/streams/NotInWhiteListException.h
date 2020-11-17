//
// Created by andremoreira9 on 05/11/20.
//

#ifndef FEUP_AEDA_PROJ_NOTINWHITELISTEXCEPTION_H
#define FEUP_AEDA_PROJ_NOTINWHITELISTEXCEPTION_H


#include <exception>
#include <ostream>
#include "utils.h"

class NotInWhiteListException : public std::exception{
    /**
   * Constructor
   * @param user - The user that originated the error
   * @param streamWhilisted - id of the streamer where de user is whitlisted
   */
public:
    NotInWhiteListException(std::string user, unsigned long long int streamWhilisted);

private:
    /**
     * Brief info about exception
     * @return
     */
    const char * what() const noexcept override;

    friend std::ostream &operator<<(std::ostream &os, const NotInWhiteListException &exception);

private:
    std::string user;
    unsigned long long int streamWhilisted;

};


#endif //FEUP_AEDA_PROJ_NOTINWHITELISTEXCEPTION_H
