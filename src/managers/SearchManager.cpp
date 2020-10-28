//
// Created by andremoreira9 on 27/10/20.
//


#include "SearchManager.h"

User *SearchManager::user(std::string userNick) const {
    Viewer * retur = new Viewer("Nuno", "nuno", Date("2001/02/25"));
    retur->changePassword("123");

    return retur;
}
