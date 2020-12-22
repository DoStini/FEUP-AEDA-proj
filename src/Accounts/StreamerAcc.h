//
// Created by Nuno Alves on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_STREAMERACC_H
#define FEUP_AEDA_PROJ_STREAMERACC_H


#include "Account.h"

class Streamer;

/**
 * StreamerAcc inherited from account to handle streamer account UI an IO
 */
class StreamerAcc : public Account {
private:
    Streamer * streamer;
public:
    /**
     * StreamerAcc constructor
     *
     * @param user User class pointer
     * @param streamZ StreamZ class pointer
     */
    StreamerAcc(User * user, StreamZ * streamZ);

    /**
     * Prompts the streamer to start a stream.
     */
    void startStream();

    /**
     * Displays the number of viewers of the stream;
     */
    void checkNumViewers();

    /**
     * Prompts the streamer to kick a user from their stream.
     */
    void kickUserFromStream();

    /**
     * Prompts the streamer to add a user to a private stream.
     */
    void addUserToPrivate();

    /**
    * Prompts the streamer to remove a user from private stream.
    */
    void removeUserFromPrivate();

    /**
     *  Prompts the streamer to end a stream.
     */
    void endStream();

    /**
     * Displays the number of followers
     */
    void checkNumFollowers();

    /**
     * @brief Displays the top Order
     */
    void displayOrder();

    /**
     * @brief Dispatches and shows an order
     */
    void dispatchOrder();
};


#endif //FEUP_AEDA_PROJ_STREAMERACC_H
