//
// Created by andre on 10/18/2020.
//

#ifndef FEUP_AEDA_PROJ_FOLLOWSTREAMEREXCEPTION_H
#define FEUP_AEDA_PROJ_FOLLOWSTREAMEREXCEPTION_H


#include <exception>
#include <ostream>

/**
 * Exception to be thrown after an error regarding the following system
 */
class FollowStreamerException : public std::exception{
public:
    /**
     * Excpetion constructor
     * @param following - Indicates if the error origninated because of already following or not following
     * @param streamer - Streamer nick
     * @param user - User nick that tried the operation
     */
    FollowStreamerException(bool following, const std::string &streamer, const std::string &user);

    const char * what() const noexcept override;

    friend std::ostream &operator<<(std::ostream &os, const FollowStreamerException &exception);

private:
    bool following;
    std::string streamer;
    std::string user;
};


#endif //FEUP_AEDA_PROJ_FOLLOWSTREAMEREXCEPTION_H
