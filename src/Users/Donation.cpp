//
// Created by adbp on 20/12/2020.
//

#include "Donation.h"
#include "iostream"

Donation::Donation(const std::string &streamerNick, int amount, unsigned avaliation_p) : streamerNick(streamerNick),amount(amount) {
    if(avaliation_p == 0 || avaliation_p > 5){
        throw NoInRangeValue("Donation avaliation", avaliation_p );
    }
    this->avaliation = avaliation_p;
}

const std::string &Donation::getStreamerNick() const {
    return streamerNick;
}

int Donation::getAmount() const {
    return amount;
}

int Donation::getAvaliation() const {
    return avaliation;
}

std::ostream &operator<<(std::ostream &os, const Donation &p) {
    os << "Donation is to " << p.getStreamerNick() << " whit the amount: " << p.getAmount() << " and avaliation: " << p.getAvaliation();
    return os;
}


DonationItem::DonationItem(Donation *donationItem): donationItem(donationItem) {}

DonationItem::DonationItem(const std::string &streamerNick, int amount, unsigned avaliation) {
    donationItem = new Donation(streamerNick,amount,avaliation);
}

Donation *DonationItem::getDonation() const {
    return donationItem;
}

const std::string &DonationItem::getStreamerNick() const {
    return donationItem->getStreamerNick();
}

int DonationItem::getAmount() const {
    return  donationItem->getAmount();
}

int DonationItem::getAvaliation() const {
    return donationItem->getAvaliation();
}

bool DonationItem::operator<(const DonationItem &comp) const {
    if(this->getAmount() == comp.getAmount()){
        if(this->getAvaliation() == comp.getAvaliation()){
            return this->getStreamerNick() < comp.getStreamerNick();
        }
        return this->getAvaliation() < comp.getAvaliation();
    }
    return this->getAmount() < comp.getAmount();
}

bool DonationItem::operator==(const DonationItem &comp) const {
    return ((this->getStreamerNick() == comp.getStreamerNick()) && (this->getDonation() == comp.getDonation())
        && (this->getAvaliation() == comp.getAvaliation()));
}

std::ostream &operator<<(std::ostream &os, const DonationItem &p) {
    os << "Donation is to " << p.getStreamerNick() << " whit the amount: " << p.getAmount() << " and avaliation: " << p.getAvaliation();
    return os;
}





