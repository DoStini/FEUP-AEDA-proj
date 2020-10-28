//
// Created by andre on 10/21/2020.
//

#ifndef FEUP_AEDA_PROJ_UTILS_H
#define FEUP_AEDA_PROJ_UTILS_H

#define VIEWER_MIN_AGE 12
#define STREAMER_MIN_AGE 15

enum streamType{
    publicType = 1,
    privateType,
    finishedType,
};

enum userType{
    viewer = 1,
    stream,
    admin,
};

enum language{
    PT_PT,
    PT_BR,
    ENG,
    SPA,
    FRE,
    GER,
    RUS,
    CHI,
    HINDI,
};


enum genres{
    gaming,
    technology,
    music,
    cooking,
    meetGreet,
};

typedef unsigned long long int ID;


#endif //FEUP_AEDA_PROJ_UTILS_H
