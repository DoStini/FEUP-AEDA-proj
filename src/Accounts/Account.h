//
// Created by Nuno Alves on 28/10/2020.
//

#ifndef FEUP_AEDA_PROJ_ACCOUNT_H
#define FEUP_AEDA_PROJ_ACCOUNT_H

#include "User.h"
#include "StreamZ.h"


class Account {
protected:
    User * user;
    StreamZ * streamZ;
public:
    virtual void run() = 0;
    void changeName();
    void changePassword();
    void deleteAccount();
    void listStreams();
    void listUsers();
    void top10StreamersViews();
    void top10StreamersLikes();
};


#endif //FEUP_AEDA_PROJ_ACCOUNT_H
