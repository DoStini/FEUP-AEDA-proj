//
// Created by andre on 10/18/2020.
//

#ifndef FEUP_AEDA_PROJ_STREAMER_H
#define FEUP_AEDA_PROJ_STREAMER_H


#include "User.h"

class Streamer : public User{
public:
    Streamer(std::string name, std::string nickName, const Date &birthDate);
    bool operator == (const Streamer & str);
private:
    static const unsigned minimumAge = 15;
};


#endif //FEUP_AEDA_PROJ_STREAMER_H
