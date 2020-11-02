//
// Created by Nuno Alves on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_ACCOUNT_H
#define FEUP_AEDA_PROJ_ACCOUNT_H

#include "User.h"
#include "WrongUserTypeException.h"
#include <unordered_map>
#include <functional>
#include <vector>



class StreamZ;
class LiveStream;

/**
 * Abstract class that handles account UI and Input
 */
class Account {
    typedef std::function<void()> Option;
    typedef std::function<bool()> OptionCheck;
protected:
    User * user;
    StreamZ * streamZ;
    unsigned nOptions;
    std::vector<Option> options;
    std::unordered_map<uint32_t, OptionCheck> optionChecks;
    std::vector<std::string> optionDescriptions;

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
     * Searches for current streams for their title/genre/language and prompts the user (if viewer) to join them.
     */
    void virtual listStreams();

    /**
     * Searches for users (with their display name) and lists them.
     */
    void listUsers();

    /**
     * Prompts the user for parameters to search for a live stream and returns a vector
     * @param[out] streams A variable where the resulting search gets put
     */
    void searchParameters(std::vector<LiveStream *> &streams);

    /**
     * Displays the leaderboard panel.
     */
    void leaderboard();

    /**
     * Diplays the account options panel.
     */
    void accountOptions();

    /**
     * Lists the top 10 streamers by views
     */
    void top10StreamersViews();

    /**
     * Lists the top 10 streamers by likes
     */
    void top10StreamersLikes();

    /**
     * Lists the top 10 oldest viewers
     */
    void top10OldestUsers();
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
};



#endif //FEUP_AEDA_PROJ_ACCOUNT_H
