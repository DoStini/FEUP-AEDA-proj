//
// Created by andremoreira9 on 29/10/20.
//

#ifndef FEUP_AEDA_PROJ_ALREADYEXISTS_H
#define FEUP_AEDA_PROJ_ALREADYEXISTS_H

#include <ostream>

/**
 * Exception to be thrown when a user or stream already exists in the database
 * @tparam T - User or Streamer
 */
template <class T>class AlreadyExists : std::exception {
public:
    /**
     * Exception constructor
     * @param value - The value that tried to be added again
     */
    explicit AlreadyExists(const T &value) : value(value) {};
    friend std::ostream &operator<<(std::ostream &os, const AlreadyExists &exist){
        os << exist.value << " already exists in the database.";
        return os;
    };
    const char * what() const noexcept override{
        return "Already in database";
    };

private:
    T value;
};


#endif //FEUP_AEDA_PROJ_ALREADYEXISTS_H
