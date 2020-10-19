//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_RESTRICTEDAGEEXCEPTION_H
#define FEUP_AEDA_PROJ_RESTRICTEDAGEEXCEPTION_H

#include <exception>
#include <string>
#include <ostream>

/**
 * Exception to be thrown when someone tries to register underage user
 */
class RestrictedAgeException : public std::exception{
public:
    RestrictedAgeException(std::string name, int age, int minAge);
    /**
     * Brief info about exception
     * @return
     */
    const char * what () const noexcept override;
    friend std::ostream &operator<<(std::ostream &os, const RestrictedAgeException &exception);

private:
    std::string name;
    int age;
    int minAge;
};


#endif //FEUP_AEDA_PROJ_RESTRICTEDAGEEXCEPTION_H
