//
// Created by andre on 10/18/2020.
//

#ifndef FEUP_AEDA_PROJ_ALREADYINSTREAMEXCEPTION_H
#define FEUP_AEDA_PROJ_ALREADYINSTREAMEXCEPTION_H

#include <exception>
#include <ostream>


/**
 * Object to be thrown when a user tries to join a stream while watching some other
 */
class AlreadyInStreamException : public std::exception {
public:
    /**
     * Constructor
     * @param user - The user that originated the error
     * @param streamWatching
     */
    AlreadyInStreamException(std::string user, std::string streamWatching);

    /**
     * Brief info about exception
     * @return
     */
    const char * what() const noexcept override;

    friend std::ostream &operator<<(std::ostream &os, const AlreadyInStreamException &exception);

private:
    std::string user;
    std::string streamWatching;
};


#endif //FEUP_AEDA_PROJ_ALREADYINSTREAMEXCEPTION_H
