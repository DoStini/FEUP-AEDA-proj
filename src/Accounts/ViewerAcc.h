//
// Created by Nuno Alves on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_VIEWERACC_H
#define FEUP_AEDA_PROJ_VIEWERACC_H

#include "Account.h"
#include "Viewer.h"

class ViewerAcc : public Account {
private:
    Viewer * viewer;
public:
    void run() override;
    void joinStream();
    void leaveStream();
    void giveFeedback();
    void findStreamFollowing();
    void followStreamer();
    void unfollowStreamer();
};


#endif //FEUP_AEDA_PROJ_VIEWERACC_H
