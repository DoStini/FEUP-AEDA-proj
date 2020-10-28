//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_USERMANAGER_H
#define FEUP_AEDA_PROJ_USERMANAGER_H

class StreamZ;


class UserManager {
public:
    UserManager(StreamZ *streamZ);

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_USERMANAGER_H
