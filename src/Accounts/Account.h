//
// Created by Nuno Alves on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_ACCOUNT_H
#define FEUP_AEDA_PROJ_ACCOUNT_H

#include "User.h"
#include "WrongUserTypeException.h"
#include <functional>
#include <vector>



class StreamZ;

/**
 * Abstract class that handles account UI and Input
 */
class Account {
    typedef std::function<void()> Option;
protected:
    User * user;
    StreamZ * streamZ;
    unsigned nOptions;
    std::vector<Option> options;
    std::vector<std::string> optionDescriptions;
public:
    /**
     * Constructor for abstract Account Class
     *
     * @param user User Class pointer
     * @param streamZ StreamZ Class pointer
     */
    Account(User * user, StreamZ * streamZ);

    virtual ~Account() = default;

    /**
     * function that displays account specific options
     */
    void run();

    /**
     * Prompts the user to change their names.
     */
    void changeName();

    /**
     * Prompts the user to change their password.
     */
    void changePassword();

    /**
     * Prompts the user to delete their account.
     */
    void deleteAccount();

    /**
     * Lists all current streams.
     */
    void listStreams();

    /**
     * Lists all Users;
     */
    void listUsers();

    /**
     * Displays the leaderboard panel.
     */
    void leaderboard();

    /**
     * Lists the top 10 streamers by views
     */
    void top10StreamersViews();

    /**
     * Lists the top 10 streamers by likes
     */
    void top10StreamersLikes();
};



#endif //FEUP_AEDA_PROJ_ACCOUNT_H
