//
// Created by andre on 10/21/2020.
//

#ifndef FEUP_AEDA_PROJ_RESTRICTEDSTREAMEXCEPTION_H
#define FEUP_AEDA_PROJ_RESTRICTEDSTREAMEXCEPTION_H

#include <string>
#include <ostream>

class RestrictedStreamException : public std::exception {
public:
    // TODO INSERT ACTUAL AGES
    RestrictedStreamException(std::string streamName, std::string userName);
    const char * what() const noexcept override;

    friend std::ostream &operator<<(std::ostream &os, const RestrictedStreamException &exception);

private:
    std::string streamName;
    std::string userName;
};


#endif //FEUP_AEDA_PROJ_RESTRICTEDSTREAMEXCEPTION_H
