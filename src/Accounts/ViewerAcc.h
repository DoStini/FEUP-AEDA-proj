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
     * Displays viewer options.
     */
    void run() override;
    /**
     * Prompts the viewer to join a stream.
     */
    void joinStream();
    /**
     * Prompts the viewer to leave a stream.
     */
    void leaveStream();
    /**
     * Prompts the user to give a stream feedback.
     */
    void giveFeedback();

    /**
     * Displays the live streams of the streamers the viewer is following.
     */
    void findStreamFollowing();

    /**
     * Prompts the user to follow a streamer.
     */
    void followStreamer();

    /**
     * Prompts the viewer to unfollow a streamer.
     */
    void unfollowStreamer();
};


#endif //FEUP_AEDA_PROJ_VIEWERACC_H
