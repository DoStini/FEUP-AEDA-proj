//
// Created by andre on 10/18/2020.
//

#ifndef FEUP_AEDA_PROJ_ALREADYINSTREAMEXCEPTION_H
#define FEUP_AEDA_PROJ_ALREADYINSTREAMEXCEPTION_H

#include <exception>
#include <ostream>
#include <utils.h>


/**
 * Object to be thrown when a user tries to join a streamer while watching some other
 */
class AlreadyInStreamException : public std::exception {
public:
    /**
     * Constructor
     * @param user - The user that originated the error
     * @param currStream - The streamer
     * @param viewer - If the user is a viewer(true) or a streamer
     */
    AlreadyInStreamException(std::string user, ID streamWatching, bool viewer = true);
    /**
     * Brief info about exception
     * @return
     */
    const char * what() const noexcept override;

    friend std::ostream &operator<<(std::ostream &os, const AlreadyInStreamException &exception);

private:
    std::string user;
    ID currStream;
    bool isViewer;
};


#endif //FEUP_AEDA_PROJ_ALREADYINSTREAMEXCEPTION_H
