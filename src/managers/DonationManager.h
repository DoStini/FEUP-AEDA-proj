//
// Created by adbp on 21/12/2020.
//

#ifndef FEUP_AEDA_PROJ_DONATIONMANAGER_H
#define FEUP_AEDA_PROJ_DONATIONMANAGER_H

class StreamZ;

#include "Donation.h"
#include "BST.h"

class DonationManager {
public:
    /**
    * Constructor. StreamZ needs to use to access the database and other methods
    * @param streamZ - Main class pointer
    */
    explicit DonationManager(StreamZ *streamZ);

    /**
     * Create a new donation in the BST
     * @throw AlreadyExist if equal donation exists, NotInRangeValue if evaluation is not valid
     * @param streamerNick - streamer nick
     * @param amount - donation value
     * @param evaluation - evaluation of the donation from 1 to 5
     */
    void creatDonation(const std::string &streamerNick, int amount, int evaluation);

    /**
     * Finds a donation in the BST
     * @param streamerNick
     * @param amount
     * @param evaluation
     * @return DonationItem copy
     */
    DonationItem findDonation(const std::string &streamerNick, int amount, int evaluation);

    /**
     * delete a donation from the BST
     * @param streamerNick - streamer nick
     * @param amount - donation value
     * @param avaliation - avaliation of the donation from 1 to 5
     */
    void deleteDonation(const std::string &streamerNick, int amount, int evaluation);

    /**
     * delete all the donations for a streamer with the specified nick
     * @param streamerNick - nick of the streamer to be removed
     */
    void deleteAllDonationsByNick(const std::string &streamerNick);

private:
    StreamZ* streamZ;
};


#endif //FEUP_AEDA_PROJ_DONATIONMANAGER_H
