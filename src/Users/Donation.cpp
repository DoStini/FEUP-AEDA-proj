//
// Created by adbp on 20/12/2020.
//

#include "Donation.h"
#include "iostream"
#include <sstream>

Donation::Donation(const std::string &streamerNick, unsigned amount, unsigned evaluation_p)
    :streamerNick(streamerNick),amount(amount) {
    if(evaluation_p == 0 || evaluation_p > 5){
        throw NotInRangeValue("Donation evaluation", evaluation_p );
    }
    this->evaluation = evaluation_p;
}

const std::string &Donation::getStreamerNick() const {
    return streamerNick;
}

unsigned Donation::getAmount() const {
    return amount;
}

unsigned Donation::getEvaluation() const {
    return evaluation;
}

std::ostream &operator<<(std::ostream &os, const Donation &p) {
    os << "Donation is to " << p.getStreamerNick() << " with the amount: " << p.getAmount() << " and evaluation: " << p.getEvaluation();
    return os;
}


DonationItem::DonationItem(Donation *donationItem): donationItem(donationItem) {}

DonationItem::DonationItem(const std::string &streamerNick, unsigned amount, unsigned evaluation) {
    donationItem = new Donation(streamerNick,amount,evaluation);
}

Donation *DonationItem::getDonation() const {
    return donationItem;
}

const std::string &DonationItem::getStreamerNick() const {
    return donationItem->getStreamerNick();
}

unsigned DonationItem::getAmount() const {
    return  donationItem->getAmount();
}

unsigned DonationItem::getEvaluation() const {
    return donationItem->getEvaluation();
}

bool DonationItem::operator<(const DonationItem &comp) const {
    if(this->getAmount() == comp.getAmount()){
        if(this->getEvaluation() == comp.getEvaluation()){
            return this->getStreamerNick() < comp.getStreamerNick();
        }
        return this->getEvaluation() < comp.getEvaluation();
    }
    return this->getAmount() < comp.getAmount();
}

bool DonationItem::operator==(const DonationItem &comp) const {
    return ((this->getStreamerNick() == comp.getStreamerNick())
        && (this->getDonation() == comp.getDonation())
        && (this->getEvaluation() == comp.getEvaluation()));
}

std::ostream &operator<<(std::ostream &os, const DonationItem &p) {
    os << "Donation is to " << p.getStreamerNick() << "amount: " << p.getAmount() << " | evaluation: " << p.getEvaluation();
    return os;
}

std::string Donation::getShortDescription() const {
    std::stringstream  ss1;
    ss1 << (*this);
    return ss1.str();
}





