//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_SEARCHMANAGER_H
#define FEUP_AEDA_PROJ_SEARCHMANAGER_H

#include "User.h"
#include "Viewer.h"


class SearchManager {
public:
    User * user(std::string userNick) const;
};


#endif //FEUP_AEDA_PROJ_SEARCHMANAGER_H
