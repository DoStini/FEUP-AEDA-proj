//
// Created by adbp on 18/10/2020.
//

#include "PublicStream.h"

#include <utility>

PublicStream::PublicStream(std::string title, language streamLanguage, genre streamGenre,std::string streamerNick, unsigned minAge) :
                        LiveStream(std::move(title), streamLanguage, streamGenre,std::move(streamerNick), minAge) {}

streamType PublicStream::getStreamType() const {
    return publicType;
}

void PublicStream::addViewer(const std::string &viewerNick) {
    streamViewers.push_back(viewerNick);
}

std::string PublicStream::getShorDescription() const {
    std::stringstream ss;
    ss << title << " (Stream Id: " << streamId << ")" << " ->Public";
    return ss.str();
}

std::string PublicStream::getLongDescription() const {
    std::stringstream ss;
    ss << "Streamed by:" << streamerNick << std::endl
    << "Star streaming: " << beginDate.getStringDate() << std::endl
    << "Language: " << streamLanguage << std::endl
    << "Genre: " << streamGenre << std::endl
    << "Necessary age to join: " << minAge << std::endl
    << "Current watching: " << streamViewers.size() << std::endl
    << "Likes: " << getLikes() << " Dislikes: " << getDislikes();
    return ss.str();

}

void PublicStream::readFromFile(std::ifstream &ff) {

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

    beginDate = Date(ss.str());

    int lang, _genre;

    ff >> sep >> lang >> sep >> _genre >> sep >> minAge >> sep >> streamerNick >> sep;

    streamLanguage = (language) lang;
    streamGenre = (genre) _genre;

    unsigned int numViewers = 0;

    // Reading streamer viewers
    ff >> numViewers >> sep;

    for(int i = 0; i < numViewers; i++){
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

}

void PublicStream::writeToFile(std::ofstream &ff) {

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

    for (int i = 0; i < getNumViewers(); ++i) {
        ff << streamViewers[i] << " , ";
    }

    // Writing feedback map

    num = likeSystem.size();

    ff << num << " , ";

    for (auto &pair : likeSystem){
        ff << pair.first << " - " << pair.second << " , ";
    }


    // Writing number of likes and dislikes
    ff << nLikes_Dislikes.first << " , " << nLikes_Dislikes.second << " , " << std::endl;

}

PublicStream::PublicStream() : LiveStream() {
}

