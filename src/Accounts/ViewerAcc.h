//
// Created by Nuno Alves on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_VIEWERACC_H
#define FEUP_AEDA_PROJ_VIEWERACC_H

#include "Account.h"

class Viewer;


/**
 *
 * ViewerAcc inherited from account to handle Viewer account UI an IO
 */
class ViewerAcc : public Account{
private:
    Viewer * viewer;
    bool checkWatchingPrivate() const;
public:
    /**
     * ViewerAcc constructor
     *
     * @param user User class pointer
     * @param StreamZ StreamZ class pointer
     */
    ViewerAcc(User * user, StreamZ * streamZ);
    ~ViewerAcc() = default;

    /**
     * Prompts the viewer to join a stream if they have their id.
     */
    void joinStreamById();

    /**
     * Display info about the currently watching stream.
     */
    void displayWatchingInfo();
    /**
     * Prompts the viewer to leave the stream they are watching.
     */
    void leaveStream();
    /**
     * Prompts the user to give a stream feedback.
     */
    void giveFeedback();

    /**
     * Prompts the user to comment on a private stream.
     */
    void giveComment();

    /**
     * Displays the live streams of the streamers the viewer is following.
     */
    void findStreamFollowing();

    /**
     * Displays all of the streamers the viewer is following
     */
     void listFollowingStreamers();

    /**
     * Prompts the user to follow a streamer.
     */
    void followStreamer();

    /**
     * Prompts the viewer to unfollow a streamer.
     */
    void unfollowStreamer();

    /**
     * Displays Streams history of the viewer
     */
    void displayHistory();

    /**
     * @brief Prompts the viewer to buy merch from a streamer.
     */
    void orderMerch();

    /**
     * @brief Prompts the viewer to remove merch from a streamer.
     */
    void removeOrder();
    /**
     * Makes a donation to a chosen streamer
     */
    void makeDonation();
};


#endif //FEUP_AEDA_PROJ_VIEWERACC_H
