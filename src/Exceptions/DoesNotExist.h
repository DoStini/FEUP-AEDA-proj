//
// Created by andremoreira9 on 28/10/20.
//

#ifndef FEUP_AEDA_PROJ_DOESNOTEXIST_H
#define FEUP_AEDA_PROJ_DOESNOTEXIST_H


#include <exception>
#include <string>
#include <ostream>


/**
 * Class to be throw when something does not exist in the database
 * @tparam T - User or Streamer
 */
template<class T>
class DoesNotExist : public std::exception {
public:
    /**
     * Exception constructor
     * @param value User nick or Stream ID that doesn't exist
     */
    explicit DoesNotExist(const T &value) : value(value) {};
    friend std::ostream &operator<<(std::ostream &os, const DoesNotExist &exist){
        os << exist.value << " does not exist in the database.";
        return os;
    };
    const char * what() const noexcept override{
        return "Not in database";
    };

private:
    T value;
};


#endif //FEUP_AEDA_PROJ_DOESNOTEXIST_H
