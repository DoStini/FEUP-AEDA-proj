//
// Created by adbp on 26/10/2020.
//

#include "FinishedStream.h"
#include "StreamZ.h"
#include <utility>
#include "utils.h"

FinishedStream::FinishedStream(std::string title, language language, genre streamGenre, int numViewers,
                               std::string streamerNick,ID streamID, streamType type)
                                : Stream(std::move(title),language,streamGenre,std::move(streamerNick)),
                                numViewers(numViewers), type(type){
    streamId = streamID;
    Date currDate; currDate.setSystemDate();
    finishedDate = currDate;

}


FinishedStream::~FinishedStream() {
    streamZ->getUserM()->removeHistoryElemFromUser(streamId);
}

streamType FinishedStream::getStreamType() const {
    return type;
}


streamState FinishedStream::getStreamState() const {
    return finished;
}

streamFileType FinishedStream::getStreamFileType() const {
    return finishedFile;
}

const Date &FinishedStream::getFinishedDate() const {
    return finishedDate;
}

unsigned int FinishedStream::getNumViewers() const {
    return numViewers;
}

std::string FinishedStream::getShortDescription() const {
    std::stringstream  ss1, ss2;
    ss1 << "| id: " << streamId;
    ss2 << std::setw(20) << std::left << title << std::setw(15) << std::left << ss1.str() <<std::setw(15) << std::left <<  "| Finished";
    return ss2.str();
}

std::string FinishedStream::getLongDescription() const {
    std::stringstream ss;
    ss << "Stream Title: " << title << std::endl
        << "Stream ID: " << streamId << std::endl
       << "Streamed by:" << streamerNick << std::endl
       << "Started streaming in: " << beginDate.getStringDate() << std::endl
       << "Stream finished: " << finishedDate.getStringDate() << std::endl
       << "Language: " << languageTypes[streamLanguage] << std::endl
       << "Genre: " << genreTypes[streamGenre] << std::endl
       << "Final viewers: " << numViewers << std::endl;

    return ss.str();
}

void FinishedStream::writeToFile(std::ofstream &ff) {

    int num = 0;
    std::string counter;
    std::stringstream temp(title);
    while (temp >> counter) num ++;

    ff << streamId << " , " << num << " , " << title << " , " << beginDate.getStringDateTime()
       << " , " << streamLanguage << " , " << streamGenre << " , " << type
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

    ss.str(std::string());    // Clearing the string streamer

    ff >> temp; ss << temp << " "; // Building date and hour/minute
    ff >> temp; ss << temp; // Building date and hour/minute

    beginDate = Date(ss.str(), true);

    int lang, _genre, _type;

    ff >> sep >> lang >> sep >> _genre >> sep >> _type >> sep >> streamerNick
       >> sep;

    streamLanguage = (language) lang;
    streamGenre = (genre) _genre;
    type = (streamType) _type;

    ss.str(std::string());    // Clearing the string streamer

    ff >> temp; ss << temp << " "; // Building date and hour/minute
    ff >> temp; ss << temp; // Building date and hour/minute

    finishedDate = Date(ss.str(), true);

    ff >> sep >> numViewers >> sep;

}

FinishedStream::FinishedStream() : Stream(){

}

