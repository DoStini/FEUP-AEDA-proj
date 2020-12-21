//
// Created by adbp on 21/12/2020.
//

#include "DonationManager.h"
#include "StreamZ.h"
#include "AlreadyExists.h"


void DonationManager::creatDonation(const string &streamerNick, int amount, int evaluation) {

    streamZ->getSearchM()->getUser(streamerNick);
    DonationItem newDonation(streamerNick,amount,evaluation);
    DonationItem fDonation = streamZ->getDatabase().donations.find(newDonation);


    if((fDonation.getStreamerNick() == "") && (fDonation.getEvaluation() == 1) && (fDonation.getAmount() == 0)) {
        streamZ->getDatabase().donations.insert(DonationItem(streamerNick, amount, evaluation));
    }
    else {
        throw AlreadyExists<DonationItem>(newDonation);
    }
}

void DonationManager::deleteDonation(const string &streamerNick, int amount, int evaluation) {
    DonationItem donation(streamerNick,amount, evaluation);
    streamZ->getDatabase().donations.remove(donation);
}

DonationManager::DonationManager(StreamZ *streamZ): streamZ(streamZ){}
