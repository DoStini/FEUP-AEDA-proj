//
// Created by Nuno Alves on 28/10/2020.
//
#pragma once

#ifndef FEUP_AEDA_PROJ_ACCOUNT_H
#define FEUP_AEDA_PROJ_ACCOUNT_H

#include "User.h"
#include "WrongUserTypeException.h"
#include <unordered_map>
#include <functional>
#include <vector>



class StreamZ;
class LiveStream;

extern const char *languageTypes[];

extern const char *genreTypes[];

typedef std::function<void()> Option;
typedef std::function<bool()> OptionCheck;

/**
 * Abstract class that handles account UI and Input
 */
class Account {
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
    /** Promps the user to deactivate their account
     */
    void disableAccount();
    /**
     * Displays the user's info.
     */
    void displaySelfInfo();

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
    * Displays stream information given an ID.
    */
    void displayStreamInfo();

    /**
     * Displays user information given a nickname.
     */
    void displayUserInfo();

    /**
     * Prompts the user to sort a list.
     *
     * @tparam T the type in the vector
     * @param toSort the vector to sort, passed by reference
     * @param sortDescriptions descriptions to be printed (MUST BE SAME SIZE AS SORTING METHODS)
     * @param sortingMethods the functions that sort the vector (MUST BE SAME SIZE AS SORT DESCRIPTIONS)
     */
    template<typename T>
    void sortingMethods(std::vector<T*> & toSort,
                        std::vector<std::string> &sortDescriptions,
                        std::vector<std::function<void()>> &sortingMethods);

    /**
     * Displays the account options panel.
     */
    void accountOptions();

    /**
     * Lists the top 10 streams by views
     */
    void top10StreamsViews();

    /**
     * Lists the top 10 streams by likes
     */
    void top10StreamsLikes();

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
