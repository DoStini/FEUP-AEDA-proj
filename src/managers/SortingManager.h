//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_SORTINGMANAGER_H
#define FEUP_AEDA_PROJ_SORTINGMANAGER_H

#include <vector>

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

    /// @return Returns the current stored Livestreams sorted by views
    std::vector<LiveStream *> sortStreamByViews() const;
    /**
     * @param streams - vector of livestreams
     * @return Returns the desired vector of livestreams sorted by views
     */
    std::vector<LiveStream *> sortStreamByViews(std::vector<LiveStream *> streams) const;

    /// @return Returns the current stored Livestreams sorted by views
    std::vector<LiveStream *> sortStreamByLikes() const;
    /**
     * @param streams - vector of livestreams
     * @return Returns the desired vector of livestreams sorted by views
     */
    std::vector<LiveStream *> sortStreamByLikes(std::vector<LiveStream *> streams) const;

    /// @return Returns the current stored Livestreams sorted by Date
    std::vector<LiveStream *> sortStreamByDate() const;
    /**
     * @param streams - vector of livestreams
     * @return Returns the desired vector of livestreams sorted by Date
     */
    std::vector<LiveStream *> sortStreamByDate(std::vector<LiveStream *> streams) const;

    /// @return Returns the current stored Livestreams sorted by views
    std::vector<User *> sortUserDate() const;

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_SORTINGMANAGER_H
