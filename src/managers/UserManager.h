//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_USERMANAGER_H
#define FEUP_AEDA_PROJ_USERMANAGER_H

#include <string>


class UserManager {
public:
    bool userExists(std::string nickName) const;

};


#endif //FEUP_AEDA_PROJ_USERMANAGER_H
