//
// Created by Nuno Alves on 28/10/2020.
//

#include "StreamerAcc.h"
#include "Streamer.h"

StreamerAcc::StreamerAcc(User *user, StreamZ * streamZ) : Account(user, streamZ){
    if(Streamer * streamer = dynamic_cast<Streamer*>(user)) {
        this->streamer = streamer;
    } else {
        throw WrongUserTypeException(UserType::streamer);
    }
}

void StreamerAcc::run() {

}
