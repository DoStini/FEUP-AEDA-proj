//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_LEADERBOARD_H
#define FEUP_AEDA_PROJ_LEADERBOARD_H


#include <Stream.h>

class StreamZ;

/**
 * Class to execute leaderboard related commands
 */
class LeaderBoard {
public:
    /**
     * Constructor. StreamZ needs to be used by the class to access the database and other methods
     * @param streamZ - Main class pointer
     */
    LeaderBoard(StreamZ *streamZ);
    /// @return Vector of stream pointers containing the top 10 streams according to the number of views
    std::vector<Stream *> top10StreamViews();
    /// @return Vector of stream pointers containing the top 10 streams according to the number of likes
    std::vector<Stream *> top10StreamLikes();
    /// @return Vector of stream pointers containing the top 10 streams according to the number of comments (private streams only)
    std::vector<Stream *> top10StreamComments();
    /// @return Vector of users pointers containing the top 10 oldest users
    std::vector<User *> top10oldestUsers();

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_LEADERBOARD_H