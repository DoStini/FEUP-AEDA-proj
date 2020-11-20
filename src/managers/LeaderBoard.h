//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_LEADERBOARD_H
#define FEUP_AEDA_PROJ_LEADERBOARD_H


#include <Stream.h>
#include <PrivateStream.h>

class StreamZ;
#include "LiveStream.h"

/**
 * Class to execute leaderboard related commands
 */
class LeaderBoard {
public:
    /**
     * Constructor. StreamZ needs to be used by the class to access the database and other methods
     * @param streamZ - Main class pointer
     */
    explicit LeaderBoard(StreamZ *streamZ);
    /// @param streams Returns by reference Vector of stream pointers containing the top 10 streams according to the number of views
    void top10StreamViews(std::vector<LiveStream *> & streams) const;
    /// @param streams Returns by reference  Vector of stream pointers containing the top 10 streams according to the number of likes minus dislikes
    void top10StreamLikes(std::vector<LiveStream *> & streams) const;
    /// @param streams Returns by reference Vector of stream pointers containing the top 10 streams according to the number of comments (private streams only)
    void top10StreamComments(std::vector<PrivateStream *> & streams) const;
    /// @param streams Returns by reference Vector of users pointers containing the top 10 oldest users in the platform (by time joined)
    void top10oldestUsersPlat(std::vector<User *> & streams) const;

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_LEADERBOARD_H