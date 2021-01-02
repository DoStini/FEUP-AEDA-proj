//
// Created by andre on 10/18/2020.
//



#ifndef FEUP_AEDA_PROJ_STREAMER_H
#define FEUP_AEDA_PROJ_STREAMER_H

#include "User.h"
#include <queue>

class MerchandisingOrder {
private:
    std::string viewerName;
    std::string streamerName;
    unsigned numMerch;
    unsigned availability;
public:
    MerchandisingOrder(std::string userName, std::string streamerName, unsigned num, unsigned avail);
    std::string getViewerName() const {return viewerName;};
    unsigned getNumMerch() const {return numMerch;};
    unsigned getAvailability() const {return availability;};
    bool operator<(const MerchandisingOrder& merchandisingOrder) const;
    bool operator==(const MerchandisingOrder& merchandisingOrder) const;
    friend std::ostream &operator<<(std::ostream &os, const MerchandisingOrder &order);
};

/**
 * Class Streamer
 * The class that contains information and methods related to the streamer
 */
class Streamer : public User {
public:

    /**
    * Constructor when creating a new user
    * Throws a RestrictedAgeException if the user is not allowed to create an account
    * @param name - Name of the user
    * @param nickName - Nickname
    * @param password - User password
    * @param birthDate - Date of Birth
    */
    Streamer(const std::string& name, std::string nickName,std::string password, const Date &birthDate);

    Streamer();
    explicit Streamer(const std::string & nick);

    ~Streamer() override;
    /// Returns the user type
    ///@return - user type = streamer
    userType getUserType() const override;
    /**
     * Disables the account
     */
    void disableAccount();
    /**
     * Reactivates the account
     * Updates account status
     */
    void reenableAccount();
    /// @return If the account is activated or disabled
    bool isActive() const;
    char getStatus() const;
    /**
     * Add viewer to the followers vector
     * @param viewerNick - nick of the viewer
     */
    void addFollower(std::string viewerNick);

    /**
     * Remove viewer from the followers vector
     * @param viewerNick - nick of the viewer
     */
    void leaveFollower(std::string viewerNick);

    ///@return - number of followers of the streamer
    unsigned int getNumFollowers() const;

    /// @return - If the streamer is currently streaming or not
    bool streaming() const;

    /// @return - The current streamer, or 0 if none
    ID getStreamID();

    /// Returns a short description with info about the user
    ///@return Short description
    std::string getShortDescription() const override;

    /// Returns a long description with info about the user
    ///@return Long description
    std::string getLongDescription(bool seePassword = false) const override;
    /// Info about all of the streamer followers
    /// @return - string with all the followers
    std::string getFollowDetails() const override;
    /// Info about all of the streams done in the past
    /// @return - string with all the streams finished
    std::string getHistoryDetails() const override;

    /**
     * Start streaming a public streamer
     * @throw AlreadyInStreamException
     * @param title - Title of the streamer
     * @param language - Stream language
     * @genre genre - Genre of the streamer
     * @param minAge - Minimal age of the streamer , 12 by default
     */
    void startPublicStream(std::string title, language streamLanguage, genre streamGenre, unsigned minAge = VIEWER_MIN_AGE);

    /**
     * Start streaming a private streamer
     * @throw AlreadyInStreamException
     * @param title - Title of the streamer
     * @param language - Stream language
     * @param genre - Genre of the streamer
     * @param minAge - Minimal age of the streamer , 12 by default
     * @param maxNumberViewers - max number of viewers that the streamer will have
     */
    void startPrivateStream(std::string title, language streamLanguage, genre streamGenre,
                            unsigned minAge = VIEWER_MIN_AGE, unsigned int maxNumberViewers = MAX_VIEWERS);

    /// Total views of the stremer
    ///@return - total number of views
    unsigned int getTotalViews();
    /// Number of viewers in the current stream
    ///@return - number of viewers in the stream
    unsigned int getStreamViewers();

    /**
     * Remove user from the streamer
     * @throw DoesNotExist
     * @param viewerNick - nick of the viewer
     */
    void kickUser(std::string viewerNick);

    /**
     * Command to end the current streaming streamer
     * NotInStreamException
     */
    void closeStream();

    /**
     * Function to be used only when deleting a streamer from the system deleting the streamer pointer
     */
    void kickedStream();
    /**
     * Remove streamer from the streamer history
     *
     * @param streamID - streamer to be removed from the history
     */
    void removeStreamHistory(ID streamID);

    /**
     * @brief Dispatches an order and returns (top of queue)
     * @return the order that was dispatched
     *
     * @throws OrdersEmptyException if orders queue is empty
     */
    MerchandisingOrder dispatchOrder();
    /**
     * @brief Adds an order to the orders queue
     * @param viewerNick nickname of the viewer buying
     * @param num number of merch queued
     * @param availability purchase availability of viewer
     *
     * @throws OrdersFullException if orders has reached full size
     */
    void addOrder(const std::string& viewerNick, unsigned num, unsigned availability);
    /**
     * @brief Removes an order from a certain viewer
     * @param viewerNick nickname of the viewer
     * @return the order removed
     *
     * @throws NoSuchOrderException if no order with the nickname given exists.
     */
    MerchandisingOrder removeOrder(const std::string & viewerNick);

    /**
     * @brief Gets the top order from the priority queue.
     * @return the order
     *
     * @throws OrdersEmptyException if there are no orders in the queue
     */
    MerchandisingOrder getOrder();

    /**
     * Checks if a streamer is in the streamer history
     * @param streamID - id of the streamer to be checked
     * @return - true if it is, otherwise false
     */
    bool isInStreamHistory(ID streamID);

    ///Compare two streamers
    bool operator == (const Streamer & str);

    /**
     * Writing user info to file
     * @param ff Current file streamer
     */
    void writeToFile(std::ofstream &ff) override;

    void writeOrders(std::ofstream &ff);
    /**
     * Reading user info from file
     * @param ff Current file streamer
    */
    void readFromFile(std::ifstream &ff) override;

private:
    ///Age of the user
    static const unsigned minimumAge = STREAMER_MIN_AGE;
    ///Number of viewers that follow the streamer
    std::vector<std::string> followedBy;
    ///Stream that streamer is streaming
    ID currStreaming = NULL_STREAM;
    /// Active account or disabled
    bool active;
    /**
     * Prevents abuse to get likes
     * 0 - Nothing
     * 1 - Should receive likes in the next stream
     * 2 - Already received likes for reactivating his account
     */
    char status;
    ///Streams that the streamer have ended
    std::vector<ID> finishedStreams;
    std::priority_queue<MerchandisingOrder> orders;
};

struct streamerHash{
    int operator()(const void * ptr) const{
        int sum = 1;
        for (int i = 0; i < (int)((Streamer*) ptr)->getNickName().size(); ++i) sum += sum*37*((Streamer*) ptr)->getNickName()[i];
        return sum;
    }
    bool operator()(const void * ptr1, const void * ptr2) const{
        return ((Streamer*) ptr1)->getNickName() == ((Streamer*) ptr2)->getNickName();
    }
};

#endif //FEUP_AEDA_PROJ_STREAMER_H
