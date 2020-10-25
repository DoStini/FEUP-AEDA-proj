//
// Created by adbp on 25/10/2020.
//

#include "LiveStream.h"

void LiveStream::giveLike(User * viewer) {
    std::string name = viewer->getName();
    if(likeSystem[name] == none) {
        likeSystem[name] = like;
        nLikes_Dislikes.first++;
    }
    else if(likeSystem[name] == dislike){
        likeSystem[name] = like;
        nLikes_Dislikes.first++;
        nLikes_Dislikes.second--;
    }
}

void LiveStream::giveDislike(User * viewer) {
    std::string name = viewer->getName();
    if(likeSystem[name] == none) {
        likeSystem[name] = dislike;
        nLikes_Dislikes.second++;
    }
    else if(likeSystem[name] == like){
        likeSystem[name] = dislike;
        nLikes_Dislikes.first--;
        nLikes_Dislikes.second++;
    }
}

void LiveStream::removeFeedBack(User *viewer) {
    std::string name = viewer->getName();
    if (likeSystem[name] == like)
        nLikes_Dislikes.first--;
    else if (likeSystem[name] == dislike)
        nLikes_Dislikes.second--;
    likeSystem[name] = none;
}