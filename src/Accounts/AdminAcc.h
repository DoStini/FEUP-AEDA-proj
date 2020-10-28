//
// Created by Nuno Alves on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_ADMINACC_H
#define FEUP_AEDA_PROJ_ADMINACC_H

#include "Account.h"
#include "Admin.h"


class AdminAcc : public Account{
private:
    Admin * admin;
public:
    void run() override;
    void numStreams();
    void viewsPerStream();
    void mostViewedType();
    void mostViewedStreamer();
    void removeUser();
    void removeStream();
};


#endif //FEUP_AEDA_PROJ_ADMINACC_H
