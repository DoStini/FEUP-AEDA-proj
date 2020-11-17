//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_SORTINGMANAGER_H
#define FEUP_AEDA_PROJ_SORTINGMANAGER_H

#include <vector>
#include <PrivateStream.h>
#include "Date.h"
class StreamZ;
class LiveStream;
class User;

/**
 * Class to store the sorting algorithms
 */
class SortingManager {
public:
    /**
    * Constructor. StreamZ needs to use to access the database and other methods
    * @param streamZ - Main class pointer
    */
    SortingManager(StreamZ *streamZ);

    /**
     * @param streams - Vector of livestreams - leave empty to sort the most recent data or send a filtered vector
     * @param reversed - Defaults to highest views to lower
     * @return Returns by reference the desired vector of livestreams sorted by views
     */
    void sortStreamByViews(std::vector<LiveStream *> & streams, bool reversed = false) const;

    /**
     * @param streams - Vector of livestreams - leave empty to sort the most recent data or send a filtered vector
     * @param reversed - Defaults to highest likes to lower
     * @return Returns by reference the desired vector of livestreams sorted by likes
     */
    void sortStreamByLikes(std::vector<LiveStream *> & streams, bool reversed = false) const;

    /**
     * @param streams - Vector of livestreams - leave empty to sort the most recent data or send a filtered vector
     * @param reversed - Defaults to highest likes to lower
     * @return Returns by reference the desired vector of livestreams sorted by likes
     */
    void sortStreamByComments(std::vector<PrivateStream *> & streams, bool reversed = false) const;

    /**
     * @param streams - Vector of livestreams - leave empty to sort the most recent data or send a filtered vector
     * @param reversed - Defaults most recent stream to oldest stream
     * @return Returns by reference the desired vector of livestreams sorted by date
     */
    void sortStreamByDate(std::vector<LiveStream *> & streams, bool reversed = false) const;

    /**
     * @param users - Vector of users - leave empty to sort the most recent data or send a filtered vector
     * @param reversed - Defaults most recent user on the platform to older
     * @return Returns by reference the desired vector of livestreams sorted by date
     */
    void sortUserDatePlatform(std::vector<User *> & users, bool reversed = false) const;

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_SORTINGMANAGER_H
