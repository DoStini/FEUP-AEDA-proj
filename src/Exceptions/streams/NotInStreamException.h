//
// Created by andre on 10/18/2020.
//

#ifndef FEUP_AEDA_PROJ_NOTINSTREAMEXCEPTION_H
#define FEUP_AEDA_PROJ_NOTINSTREAMEXCEPTION_H

#include <exception>
#include <string>
#include <ostream>

/**
 * Object to be thrown when a user does something that requires to be in a stream
 */
class NotInStreamException : public std::exception {
public:
    /**
     * Constructor
     * @param user - The user trying to join a new stream
     */
    NotInStreamException(std::string userName);
    /**
     * Brief info about exception
     * @return
     */
    const char * what() const noexcept override;

    friend std::ostream &operator<<(std::ostream &os, const NotInStreamException &exception);

private:
    std::string userName;
};


#endif //FEUP_AEDA_PROJ_NOTINSTREAMEXCEPTION_H
