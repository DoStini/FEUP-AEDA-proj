//
// Created by andremoreira9 on 27/10/20.
//

#ifndef FEUP_AEDA_PROJ_SEARCHMANAGER_H
#define FEUP_AEDA_PROJ_SEARCHMANAGER_H

#include <climits>
#include "User.h"
#include "Stream.h"
#include "PrivateStream.h"
#include "DoesNotExist.h"
#include "Donation.h"

class StreamZ;

class User;
class LiveStream;

/**
 * Template function to check if a certain element is present in the vector
 * @tparam T - Type of data
 * @param vec - Vector of T elements
 * @param toFind - Value to check
 * @return If toFind is in the vector
 */
template <class T>
bool checkParam(const std::vector<T> & vec, T toFind){
    return std::find_if(vec.begin(),
                     vec.end(),
                     [toFind](T currVal){
                        return currVal == toFind;
                     }) != vec.end();
}


/**
 * Class to execute search methods over the database
 */
class SearchManager {
public:
    /**
     * Constructor. StreamZ needs to be used by the class to access the database and other methods
     * @param streamZ - Main class pointer
     */
    SearchManager(StreamZ *streamZ);
    /**
     * @param nick - Nickname of the user
     * @return If a user with that nickname exists
     */
    bool userExists(std::string nick) const;
    /**
     * @param nick - Nickname of the viewer
     * @return If a viewer with that nickname exists
     */
    bool viewerExists(std::string nick) const;
    /**
     * @param nick - Nickname of the streamer
     * @return If a streamer with that nickname exists
     */
    bool streamerExists(std::string nick) const;
    /**
     * @param streamID - The id of the stream
     * @return If a stream with that ID exists
     */
    bool streamExists(ID streamID) const;
    /// @return If an admin account was already created
    bool adminExists() const;
    /**
     * @throws DoesNotExist if user does not exist
     *  @return Corresponding user to the nickname
     */

    User * getUser(std::string userNick) const;
    /// @return Corresponding stream to the streamID
    Stream * getStream(ID streamID) const;
    /**
     * @param name - Name of user to be searched
     * @return Vector of users with the specified name
     */
    void listUsers(std::vector<User *> & users, const std::string& name = "") const;

    /**
     * Function to list all streams the viewer is allowed to watch
     * @param streams - Returns by reference the vector of streams corresponding to the specified params - Will be cleared if not empty
     * @param streamName - Optional param specifying the name of the streams to search
     * @param genres - Optional param specifying the genre(s) of the streams to search
     * @param langs - Optional param specifying the language(s) of the streams to search
     */
    void listAllowedLiveStreams(std::vector<LiveStream *> & streams, std::string viewerNick,  const std::string& streamName = "",
                                const std::vector<genre> & genres = std::vector<genre>(),
                                const std::vector<language> & langs = std::vector<language>()) const;
    /**
     * @param Returns by reference the vector of streams corresponding to the specified params - Will be cleared if not empty
     * @param streamName - Optional param specifying the name of the streams to search
     * @param genres - Optional param specifying the genre(s) of the streams to search
     * @param langs - Optional param specifying the language(s) of the streams to search
     */
    void listLiveStreams(std::vector<LiveStream *> & streams, const std::string& streamName = "",
                                          unsigned minAge = VIEWER_MIN_AGE,
                                          const std::vector<genre> & genres = std::vector<genre>(),
                                          const std::vector<language> & langs = std::vector<language>()) const;

    /**
     * List live streams corresponding to some streamers
     * Usefull to get a vector according to the following streamers of a viewer
     * @param streams - Returns by reference the vector of livestreams from the streamers - Will be cleared if not empty
     * @param streamerID - Vector of streamer ID's
     */
    void listLiveStreamsByStreamers(std::vector<LiveStream *> &streams, const std::vector<std::string> &streamerNick) const;
    /**
     * Lists all private streams
     * @param streams
     */
    void listPrivateLiveStreams(std::vector<PrivateStream *> & streams) const;

    /**
     * List donation corresponding to certain parameters
     * @param donations - Returns by reference the vector of donations - Will be cleared if not empty
     * @param streamersNicks - Optional param specifying the name of the streams to search
     * @param minAmount - Optional param specifying the min amount to search
     * @param maxAmount - Optional param specifying the max amount to search
     * @param evaluations - Optional param specifying the evaluations to search
     */
    void listDonations(std::vector<Donation*> & donations,
                       std::vector<std::string> streamersNicks =  std::vector<std::string>(),
                       unsigned minAmount = 0 , unsigned maxAmount = UINT_MAX ,
                       const std::vector<unsigned> & evaluations = std::vector<unsigned>()) const;

private:
    StreamZ * streamZ;
};


#endif //FEUP_AEDA_PROJ_SEARCHMANAGER_H

