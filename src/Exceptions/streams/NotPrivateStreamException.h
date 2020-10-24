//
// Created by adbp on 24/10/2020.
//

#ifndef FEUP_AEDA_PROJ_NOTPRIVATESTREAMEXCEPTION_H
#define FEUP_AEDA_PROJ_NOTPRIVATESTREAMEXCEPTION_H

#include <exception>
#include <string>
#include <ostream>

class NotPrivateStreamException : public std::exception {
public:
    /**
     * Constructor
     * @param stream - The stream that is not private
     */
    NotPrivateStreamException(std::string streamName);
    /**
     * Brief info about exception
     * @return
     */
    const char * what() const noexcept override;

    friend std::ostream &operator<<(std::ostream &os, const NotPrivateStreamException &exception);

private:
    std::string streamName;
};


#endif //FEUP_AEDA_PROJ_NOTPRIVATESTREAMEXCEPTION_H
