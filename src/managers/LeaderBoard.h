//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_LEADERBOARD_H
#define FEUP_AEDA_PROJ_LEADERBOARD_H


#include <Stream.h>

class LeaderBoard {
public:
    LeaderBoard() = default;
    std::vector<Stream *> top10StreamViews();
    std::vector<Stream *> top10StreamLikes();
    std::vector<User *> top10oldestUsers();
};


#endif //FEUP_AEDA_PROJ_LEADERBOARD_H
