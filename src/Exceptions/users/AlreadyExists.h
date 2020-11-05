//
// Created by andremoreira9 on 29/10/20.
//

#ifndef FEUP_AEDA_PROJ_ALREADYEXISTS_H
#define FEUP_AEDA_PROJ_ALREADYEXISTS_H

#include <ostream>

template <class T>
class AlreadyExists : std::exception {
public:
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