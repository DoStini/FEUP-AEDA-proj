//
// Created by Nuno Alves on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_ADMINACC_H
#define FEUP_AEDA_PROJ_ADMINACC_H

#include "Account.h"

class Admin;

/**
 * AdminAcc inherited from account to handle admin account UI an IO
 */
class AdminAcc : public Account{
private:
    Admin * admin;
    /**
     * Gets a time interval
     * @param[out] dateInterval interval is stored here
     * @return a bool that indicates if an interval was given
     */
    static bool getTimeInterval(std::pair<Date, Date> &dateInterval);
public:
    /**
     * Admin Account Constructor
     *
     * @param user User class pointer
     * @param streamZ StreamZ class pointer
     */
    AdminAcc(User * user, StreamZ * streamZ);

    /**
     * Lists the number of all streams ever created.
     */
    void numStreamsAll();

    /**
     * Lists the current number of streams.
     */
    void numStreams();

    /**
     * Lists the number of streams of a certain type in an interval of time.
     */
    void numStreamsType();

    /**
     * Displays the mean views per stream. (optional date interval exists)
     */
    void viewsPerStream();

    /**
     * Displays the most viewed type of stream.
     */
    void mostViewedType();

    /**
     * Displays the most viewed streamer.
     */
    void mostViewedStreamer();

    /**
     * Displays the most viewed genre.
     */
    void mostViewedGenre();

    /**
     * Displays the most viewed language.
     */
    void mostViewedLanguage();

    /**
     * Prompts the admin to remove a user.
     */
    void removeUser();

    /**
     * Prompts the admin to remove a stream.
     */
    void removeStream();

    /**
     * Removes a donation from the database
     */
    void removeDonation();

    /**
     * Displays the statistics panel.
     */
    void statistics();

    /**
     * @brief Prompts the admin to change orders size
     */
    void changeMaxOrders();

    /**
     * @brief Displays order size.
     */
    void displayMaxOrders();
    /**
     * Displays a list of the chosen donations parameters
     */
    void listDonations();
};


#endif //FEUP_AEDA_PROJ_ADMINACC_H
