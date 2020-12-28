//
// Created by adbp on 20/12/2020.
//
#ifndef FEUP_AEDA_PROJ_DONATION_H
#define FEUP_AEDA_PROJ_DONATION_H

#include <string>
#include "NotInRangeValue.h"
#include "ostream"

class Donation {
public:
    /**
     * Constructor for the donations
     *
     * @param streamerNick - nick of the streamer that the donation is for
     * @param amount - value of the donation
     * @param evaluation - evaluation given by donator from 1 to 5
     */
    Donation(const std::string &streamerNick, unsigned amount, unsigned evaluation);

    /**
     * Get streamer Nick
     * @return - nick of the streamer that the donation is for
     */
    const std::string &getStreamerNick() const;

    /**
     * Value of the donation
     * @return - amount of the donation
     */
    unsigned getAmount() const;

    /**
     * Get evaluation
     * @return - evaluation value 1-5
     */
    unsigned getEvaluation() const;

    /**
     * Class used as node od the BST
     */
    friend class DonationItem;

    /**
     * Used to print info about the donation
     * @param os - output stream
     * @param p - parameter
     * @return - output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Donation& p);

    /**
     * Gives shot description about the donation
     * @return
     */
    std::string getShortDescription() const;

private:
    std::string streamerNick;
    unsigned amount;
    unsigned evaluation;
};


class DonationItem {
public:
    /**
     * Constructor to create a donation node from a already existing donation
     * @param donationItem
     */
    explicit DonationItem(Donation* donationItem);

    /**
     * Constructor to create a donation node completely new
     *
     * @param streamerNick - nick of the streamer that the donation is for
     * @param amount - value of the donation
     * @param evaluation - evaluation given by donator from 1 to 5
     */
    DonationItem(const std::string &streamerNick, unsigned amount, unsigned evaluation);

    /**
     * Get pointer to the donation
     * @return - donation pointer
     */
    Donation* getDonation() const;

    /**
     * Get streamer Nick
     * @return - nick of the streamer that the donation is for
     */
    const std::string &getStreamerNick() const;

    /**
     * Value of the donation
     * @return - amount of the donation
     */
    unsigned getAmount() const;

    /**
     * Get evaluation
     * @return - evaluation value 1-5
     */
    unsigned getEvaluation() const;

    /**
     * Operator used to compare nodes
     * @param comp - item to be compared with
     * @return - comparation value
     */
    bool operator<(const DonationItem& comp) const;

    /**
     * Operator used to compare nodes
     * @param comp - item to be compared with
     * @return - comparation value
     */
    bool operator==(const DonationItem& comp) const;

    /**
     * Used to print info about the donation
     * @param os - output stream
     * @param p - parameter
     * @return - output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const DonationItem& p);

private:
    Donation* donationItem; /// pointer to the donation element
};


#endif //FEUP_AEDA_PROJ_DONATION_H
