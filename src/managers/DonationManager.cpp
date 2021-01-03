//
// Created by adbp on 21/12/2020.
//

#include "DonationManager.h"
#include "StreamZ.h"
#include "AlreadyExists.h"


void DonationManager::creatDonation(const string &streamerNick, int amount, int evaluation) {

    streamZ->getSearchM()->getUser(streamerNick);
    DonationItem newDonation(streamerNick,amount,evaluation);
    DonationItem fDonation = findDonation(newDonation);


    if((fDonation.getStreamerNick() == "") && (fDonation.getEvaluation() == 1) && (fDonation.getAmount() == 0)) {
        streamZ->getDatabase().donations.insert(DonationItem(streamerNick, amount, evaluation));
    }
    else {
        throw AlreadyExists<DonationItem>(newDonation);
    }
}

void DonationManager::deleteDonation(const string &streamerNick, int amount, int evaluation) {
    DonationItem donation = findDonation(streamerNick, amount,evaluation);
    if(donation.getStreamerNick().empty())
        throw DoesNotExist<DonationItem>(donation);
    streamZ->getDatabase().donations.remove(donation);
}

DonationManager::DonationManager(StreamZ *streamZ): streamZ(streamZ){}

void DonationManager::deleteAllDonationsByNick(const string &streamerNick) {
    bool endReach = false;
    while (!endReach) {
        endReach = true;
        BSTItrIn<DonationItem> it(streamZ->getDatabase().donations);
        while (!it.isAtEnd()) {
            if (it.retrieve().getStreamerNick() == streamerNick) {
                DonationItem temp = it.retrieve();
                streamZ->getDatabase().donations.remove(temp);
                endReach = false;
                break;
            }
            it.advance();
        }
    }

}

DonationItem DonationManager::findDonation(const string &streamerNick, int amount, int evaluation) {
    return streamZ->getDatabase().donations.find(DonationItem(streamerNick, amount, evaluation));
}
