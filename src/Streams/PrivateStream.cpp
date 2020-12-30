//
// Created by adbp on 18/10/2020.
//

#include "PrivateStream.h"
#include <utility>
#include "StreamZ.h"
#include "utils.h"

extern const char *languageTypes[];

extern const char *genreTypes[];

PrivateStream::PrivateStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick,
                                unsigned int minAge, unsigned maxViewers) : LiveStream(std::move(title),
                                    streamLanguage, streamGenre,std::move(streamerNick), minAge), maxViewers(maxViewers) {}

unsigned PrivateStream::getNumberComments() {
    return comments.size();
}

streamType PrivateStream::getStreamType() const {
    return privateType;
}

streamFileType PrivateStream::getStreamFileType() const {
    return privateFile;
}

bool PrivateStream::isValidUser(const std::string& userNick) {
    return (std::find(whitelist.begin(),whitelist.end(),userNick) != whitelist.end());
}

void PrivateStream::addValidUser(const std::string& userNick) {

    if(!streamZ->getSearchM()->viewerExists(userNick))
        throw DoesNotExist<std::string>(userNick);
    if( isValidUser(userNick) )
        throw AlreadyInWhiteListException(userNick,this->getStreamId()) ;
    whitelist.push_back(userNick);
}

void PrivateStream::kickValidUser(const std::string &userNick) {

    auto it = std::find(whitelist.begin(),whitelist.end(),userNick);
    if(it == whitelist.end())
        throw NotInStreamException(userNick);
    else {
        whitelist.erase(it);

        auto viewer = (Viewer *) streamZ->getSearchM()->getUser(userNick);
        if (viewer->getCurrWatching() == streamId)
            viewer->leaveStream();
    }
}

void PrivateStream::removeUserFromWhitelist(const std::string &userNick) {
    auto it = std::find(whitelist.begin(),whitelist.end(),userNick);
    if(it == whitelist.end())
        throw NotInStreamException(userNick);
    else
        whitelist.erase(it);
}

int PrivateStream::getWhitelistSize() const {
    return whitelist.size();
}

void PrivateStream::addComment(const std::string & text,const std::string & userNick) {
    Comment comment(text,userNick);
    comments.push_back(comment);
}

unsigned int PrivateStream::getMaxViewers() const {
    return maxViewers;
}

void PrivateStream::addViewer(const std::string &viewerNick) {
    if(this->getNumViewers() == maxViewers)
        throw MaxViewersReach(streamId, maxViewers);
    else
        streamViewers.push_back(viewerNick);
}

std::string PrivateStream::getShortDescription() const {
    std::stringstream  ss1, ss2;
    ss1 << "| id: " << streamId;
    ss2 << std::setw(20) << std::left << title << std::setw(15) << std::left << ss1.str() <<std::setw(15) << std::left <<  "| Private";
    return ss2.str();
}

std::string PrivateStream::getLongDescription() const {
    std::stringstream ss;
    ss << "Stream Title: " << title << std::endl
        << "Stream ID: " << streamId << std::endl
       << "Streamed by: " << streamerNick << std::endl
       << "Private stream" << std::endl
       << "Started streaming in: " << beginDate.getStringDate() << std::endl
       << "Language: " << languageTypes[streamLanguage] << std::endl
       << "Genre: " << genreTypes[streamGenre] << std::endl
       << "Necessary age to join: " << minAge << std::endl
       << "Currently watching: " << streamViewers.size() << std::endl
       << "Can only have a total of " << maxViewers << " viewers watching." << std::endl
       << "Likes: " << getLikes() << " Dislikes: " << getDislikes() << std::endl
       << "My comments!" << std::endl;
    for(auto it=comments.begin(); it!=comments.end(); it++){
        ss << (*it) << std::endl;
    }
    return ss.str();

}


void PrivateStream::writeToFile(std::ofstream &ff) {

    int num = 0;
    std::string counter;
    std::stringstream temp(title);
    while (temp >> counter) num ++;

    ff << streamId << " , " << num << " , " << title << " , " << beginDate.getStringDateTime()
       << " , " << streamLanguage << " , " << streamGenre << " , " << minAge
       << " , " << streamerNick << " , ";

    num = (int)getNumViewers();

    // Write viewers to file
    ff << num << " , ";

    for (unsigned int i = 0; i < getNumViewers(); ++i) {
        ff << streamViewers[i] << " , ";
    }

    // Writing feedback map

    num = likeSystem.size();

    ff << num << " , ";

    for (auto &pair : likeSystem){
        ff << pair.first << " - " << pair.second << " , ";
    }


    // Writing number of likes and dislikes
    ff << nLikes_Dislikes.first << " , " << nLikes_Dislikes.second << " , ";

    // Writing comments
    num = comments.size();

    ff << num << " , ";



    for (auto &comment : comments)
    {
        num = 0;
        std::stringstream temp(std::string(comment.comment));

        while (temp >> counter) num ++;

        ff << num << " , " << comment.comment << " , " << comment.viewerNick << " , ";
    }


    // Writing WhiteList

    num = whitelist.size();

    ff << num << " , ";

    for(auto & nick : whitelist)
        ff << nick << " , ";

    ff << maxViewers << " , " << std::endl;

}

void PrivateStream::readFromFile(std::ifstream &ff) {
    int num;
    char sep;

    std::string temp;
    std::stringstream ss;

    ff >> streamId >> sep >> num >> sep;

    for (int i = 0; i < num; ++i) {
        ff >> temp;
        ss << temp << (i == num-1 ? "" : " ");
    }

    title =  ss.str();

    ff >> sep;

    ss.str(std::string());    // Clearing the string streamer

    ff >> temp; ss << temp << " "; // Building date and hour/minute
    ff >> temp; ss << temp; // Building date and hour/minute

    beginDate = Date(ss.str(), true);

    int lang, _genre;

    ff >> sep >> lang >> sep >> _genre >> sep >> minAge >> sep >> streamerNick >> sep;

    streamLanguage = (language) lang;
    streamGenre = (genre) _genre;

    unsigned int numViewers = 0;

    // Reading streamer viewers
    ff >> numViewers >> sep;

    for(unsigned int i = 0; i < numViewers; i++){
        ff >> temp >> sep;
        streamViewers.push_back(temp);
    }

    // Reading like system
    ff >> num >> sep;

    int _feedback;

    for (int i = 0; i < num; i++){
        ff >> temp >> sep >> _feedback >> sep;
        likeSystem.insert(std::pair<std::string, feedback>(temp, (feedback) _feedback ));
    }

    // Reading number of likes and dislikes
    std::pair<unsigned, unsigned > likes;
    ff >> likes.first >> sep >> likes.second >> sep;

    nLikes_Dislikes = likes;

    // Read comments
    ff >> num >> sep;

    for (int i = 0; i < num; ++i) {
        int numComments;
        ff >> numComments >> sep;

        ss.str(std::string());    // Clearing the string streamer
        for (int j = 0; j < numComments; ++j) {
            ff >> temp;
            ss << temp << (j == num-1 ? "" : " ");
        }

        Comment comment(ss.str(), "");
        ff >> sep >> comment.viewerNick >> sep;

        comments.push_back(comment);

    }


    // Read WhiteList

    ff >> num >> sep;

    for (int i = 0; i < num; ++i)
    {
        ff >> temp >> sep;
        whitelist.push_back(temp);
    }
    ff >> maxViewers >> sep;

}

PrivateStream::PrivateStream() : LiveStream(){

}



