//
// Created by andre on 10/21/2020.
//

#ifndef FEUP_AEDA_PROJ_UTILS_H
#define FEUP_AEDA_PROJ_UTILS_H

#define VIEWER_MIN_AGE 12
#define STREAMER_MIN_AGE 15

#define NULL_STREAM 0

#define MAX_VIEWERS 10

enum streamType{
    publicType = 1,
    privateType
};

enum streamFileType{
    publicFile = 1,
    privateFile,
    finishedFile
};

enum streamState{
    livestream,
    finished
};

enum userType{
    viewer = 1,
    streamer,
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


enum genre{
    gaming,
    technology,
    music,
    cooking,
    meetGreet,
};

typedef unsigned long long int ID;


#endif //FEUP_AEDA_PROJ_UTILS_H
