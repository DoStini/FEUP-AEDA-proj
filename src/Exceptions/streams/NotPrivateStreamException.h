//
// Created by adbp on 24/10/2020.
//

#ifndef FEUP_AEDA_PROJ_NOTPRIVATESTREAMEXCEPTION_H
#define FEUP_AEDA_PROJ_NOTPRIVATESTREAMEXCEPTION_H

#include <exception>
#include <string>
#include <ostream>

/**
 * Exception to be thrown when an operation specific to private streams is done on a public stream
 */
class NotPrivateStreamException : public std::exception {
public:
    /**
     * Constructor
     * @param streamId - The streamer that is not private
     */
    explicit NotPrivateStreamException(unsigned long long int streamId);
    /**
     * Brief info about exception
     * @return
     */
    const char * what() const noexcept override;

    friend std::ostream &operator<<(std::ostream &os, const NotPrivateStreamException &exception);

private:
    unsigned long long int streamId;
};


#endif //FEUP_AEDA_PROJ_NOTPRIVATESTREAMEXCEPTION_H
