//
// Created by andremoreira9 on 08/11/20.
//

#ifndef FEUP_AEDA_PROJ_EMPTYDATABASEEXCEPTION_H
#define FEUP_AEDA_PROJ_EMPTYDATABASEEXCEPTION_H


#include <ostream>

/**
 * Exception to be thrown when database is empty
 */
class EmptyDatabaseException : std::exception {
public:
    /**
     * Constructor
     * @param users - Weather it comes from users(true) database or from streams(false)
     */
    explicit EmptyDatabaseException(bool users);

    friend std::ostream &operator<<(std::ostream &os, const EmptyDatabaseException &database);

    const char * what() const noexcept override;

private:
    bool users;
};


#endif //FEUP_AEDA_PROJ_EMPTYDATABASEEXCEPTION_H
