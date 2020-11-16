//
// Created by adbp on 26/10/2020.
//

#include "FinishedStream.h"
#include "StreamZ.h"
#include <utility>


FinishedStream::FinishedStream(std::string title, language language, genre streamGenre, int numViewers, std::string streamerNick,ID streamID)
                                : Stream(std::move(title),language,streamGenre,std::move(streamerNick)), numViewers(numViewers){
    streamId = streamID;
    Date currDate; currDate.setSystemDate();
    finishedDate = currDate;
}


FinishedStream::~FinishedStream() {
    streamZ->getUserM()->removeHistoryElemFromUser(streamId);
}

streamType FinishedStream::getStreamType() const {
    return finishedType;
}

const Date &FinishedStream::getFinishedDate() const {
    return finishedDate;
}

int FinishedStream::getNumViewers() const {
    return numViewers;
}

std::string FinishedStream::getShorDescription() const {
    std::stringstream ss;
    ss << title << " (Stream Id: " << streamId << ")" << " ->Finished";
    return ss.str();
}

std::string FinishedStream::getLongDescription() const {
    std::stringstream ss;
    ss << "Streamed by:" << streamerNick << std::endl
       << "Star streaming: " << beginDate.getStringDate() << std::endl
       << "Language: " << streamLanguage << std::endl
       << "Genre: " << streamGenre << std::endl
       << "Final viewers: " << numViewers << std::endl
       << "Stream finished at: " << finishedDate.getStringDate();
    return ss.str();
}

void FinishedStream::writeToFile(std::ofstream &ff) {

    int num = 0;
    std::string counter;
    std::stringstream temp(title);
    while (temp >> counter) num ++;

    ff << streamId << " , " << num << " , " << title << " , " << beginDate.getStringDateTime()
       << " , " << streamLanguage << " , " << streamGenre
       << " , " << streamerNick << " , " << finishedDate.getStringDateTime()
       << " , " << numViewers << " , " << std::endl;

}

void FinishedStream::readFromFile(std::ifstream &ff) {

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

    ss.str(std::string());    // Clearing the string stream

    ff >> temp; ss << temp << " "; // Building date and hour/minute
    ff >> temp; ss << temp; // Building date and hour/minute

    beginDate = Date(ss.str());

    int lang, _genre;

    ff >> sep >> lang >> sep >> _genre >> sep >> streamerNick
       >> sep;

    streamLanguage = (language) lang;
    streamGenre = (genre) _genre;

    ss.str(std::string());    // Clearing the string stream

    ff >> temp; ss << temp << " "; // Building date and hour/minute
    ff >> temp; ss << temp; // Building date and hour/minute

    finishedDate = Date(ss.str());

    ff >> sep >> numViewers >> sep;

}

FinishedStream::FinishedStream() : Stream() {

}
