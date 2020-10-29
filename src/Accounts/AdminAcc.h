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
public:
    /**
     * Admin Account Constructor
     *
     * @param user User class pointer
     * @param streamZ StreamZ class pointer
     */
    AdminAcc(User * user, StreamZ * streamZ);

    /**
     * Lists the number of streams.
     */
    void numStreams();

    /**
     * Displays the mean views per stream().
     */
    void viewsPerStream();

    /**
     * Displays the most viewed genre of stream.
     */
    void mostViewedType();

    /**
     * Displays the most viewed genre.
     */
    void mostViewedStreamer();

    /**
     * Prompts the admin to remove a user.
     */
    void removeUser();

    /**
     * Prompts the admin to remove a stream.
     */
    void removeStream();

    /**
     * Displays the statistics panel.
     */
    void statistics();
};


#endif //FEUP_AEDA_PROJ_ADMINACC_H
