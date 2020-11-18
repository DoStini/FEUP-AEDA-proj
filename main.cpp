#include<iostream>
#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "Viewer.h"
#include "Date.h"
#include "PrivateStream.h"
#include "PublicStream.h"
#include "StreamZ.h"


using testing::Eq;

TEST(test, createUsers){

    EXPECT_THROW(Viewer("Andre Moreira", "gordoMan","random", Date(2009,3,9)), RestrictedAgeException);
    try{
        Viewer v1("Andre Moreira", "gordoMan","random", Date(2009,3,9));
    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;

        if(strcmp(ex.what(), "Minimum age failed") != 0){
            auto *e = dynamic_cast<RestrictedAgeException *>(&ex);
            std::cout << *e << std::endl;
        }
    }

    EXPECT_THROW(Streamer("Andre Moreira", "gordoxgames","random", Date(2006,1,1)), RestrictedAgeException);

    Streamer sir("classy man", "classy-sir","random", Date(2001,1,1));
    std::cout << "JCL JOINED: " << sir.getJoinedPlatformDate().getStringDateTime() << std::endl;
    EXPECT_EQ(sir.getBirthDate().getStringDate(), "01/01/2001");
    EXPECT_EQ(sir.getName(), "classy man");
}

/*
TEST(test, publicStream) {
    PublicStream s1("Nice streamer", PT_PT,gaming,"unknow",12);
    ASSERT_EQ(s1.getTitle(), "Nice streamer");
    ASSERT_EQ(s1.getMinAge(), 12);
    ASSERT_EQ(s1.getNumViewers(), 0);
    Viewer v1("Andre Moreira", "gordoMan", Date(1999,3,9));
    Viewer v2("Andre Moreira", "gordox2", Date(1999,3,9));
    s1.addViewer(v1.getNickName());
    ASSERT_EQ(s1.getNumViewers(), 1);
    s1.addViewer(v2.getNickName());
    ASSERT_EQ(s1.getNumViewers(), 2);

}
*/

/*TEST(test, user_private_stream) {
    PublicStream sp("Nice open source streamer", PT_PT,gaming,"unknow",12);
    PrivateStream s1("Nice streamer", PT_PT,gaming,"unknow",12,5);
    ASSERT_EQ(s1.getTitle(), "Nice streamer");
    ASSERT_EQ(s1.getMinAge(), 12);
    ASSERT_EQ(s1.getNumViewers(), 0);
    Viewer v1("Andre Moreira", "gordoMan", Date(1999, 3, 9));
    Viewer v2("Andre Moreira", "gordox2", Date(1999, 3, 9));

    EXPECT_THROW(v1.joinStream(s1.getStreamId()), RestrictedStreamException);
    EXPECT_THROW(v2.joinStream(s1.getStreamId()), RestrictedStreamException);

    s1.addValidUser(v1.getNickName());
    v1.joinStream(s1.getStreamId());
    EXPECT_EQ(s1.getNumViewers(), 1);

    try{
        v2.joinStream(s1.getStreamId());
    } catch (std::exception & e) {
        if(strcmp(e.what(), "User not whitelisted"))
            std::cout << *( dynamic_cast<RestrictedStreamException *>(&e) ) << std::endl;
    }

    EXPECT_THROW(v1.joinStream(sp.getStreamId()), AlreadyInStreamException);

}*/

/*
TEST(test, createDateString){
    Date d1 = Date("2001/05/23");
    EXPECT_EQ(d1.getYear(), 2001);
    EXPECT_EQ(d1.getMonth(), 5);
    EXPECT_EQ(d1.getDay(), 23);

    EXPECT_THROW(Date("1899/05/23"), InvalidDate);
    EXPECT_THROW(Date("2019/02/29"), InvalidDate);
    EXPECT_THROW(Date("2019/02/29"), InvalidDate);

    Date d3 = Date();
    std::cout << d3.getYear() << "/";
    std::cout << d3.getMonth() << "/";
    std::cout << d3.getDay() << std::endl;

    EXPECT_THROW(Date("2010/13/23"), BadDateFormat);
    EXPECT_THROW(Date("2010t12t23"), BadDateFormat);
    Date d4 = Date("2010 12 23");
    EXPECT_EQ(d4.getMonth(), 12);
    Date d5 = Date("2010-12-12");
    EXPECT_EQ(d5.getDay(), 12);
}

TEST(test, createDate){
    Date d1 = Date(2001, 5, 23);
    EXPECT_EQ(d1.getYear(), 2001);
    EXPECT_EQ(d1.getMonth(), 5);
    EXPECT_EQ(d1.getDay(), 23);

    EXPECT_THROW(Date(1899, 05, 23), InvalidDate);
    EXPECT_THROW(Date(2019,02,29), InvalidDate);
    EXPECT_THROW(Date(2019,02,29), InvalidDate);

    Date d3 = Date();
    std::cout << d3.getYear() << "/";
    std::cout << d3.getMonth() << "/";
    std::cout << d3.getDay() << std::endl;

    EXPECT_THROW(Date(2010,13,23), InvalidDate);
}

TEST(test, yearDiff){
    Date d1 = Date("2000/02/25");
    Date d2 = Date("2020/02/25");
    int diff = d2.getYearDifference(d1);
    EXPECT_EQ(diff, 20);

    Date d3 = Date("2001/02/25");
    diff = d3.getYearDifference(d1);
    EXPECT_EQ(diff, 1);

    Date d8 = Date("2001/03/01");
    Date d9 = Date("2004/03/01");
    diff = d9.getYearDifference(d8);
    EXPECT_EQ(diff, 3);

    Date d7 = Date("2002/02/25");
    diff = d7.getYearDifference(d3);
    EXPECT_EQ(diff, 1);

    Date d4 = Date("2020/02/24");
    diff = d4.getYearDifference(d1);
    EXPECT_EQ(diff, 19);

    Date d5 = Date("2600/02/24");
    diff = d5.getYearDifference(d1);
    EXPECT_EQ(diff, 599);

    Date d6 = Date("2600/02/25");
    diff = d6.getYearDifference(d1);
    EXPECT_EQ(diff, 600);
}

TEST(test, hourMinute) {
    Date d1 = Date();
    std::cout << d1.getMinute() << std::endl;
    std::cout << d1.getHour() << std::endl;
    std::cout << d1.getStringDateTime() << std::endl;
    std::cout << d1.getStringDate() << std::endl;

    Date d3 = Date("2010/04/23 23:00");
    EXPECT_EQ(d3.getHour(), 23);

    Date d2 = Date(2001, 02, 25, 12, 3);
    EXPECT_EQ(d2.getStringDateTime(), "25/02/2001 12:03");

    Date d4 = Date("2001/05/03 02:02");
    EXPECT_EQ(d4.getYear(), 2001);
    EXPECT_EQ(d4.getMonth(), 5);
    EXPECT_EQ(d4.getDay(), 3);
    EXPECT_EQ(d4.getHour(), 2);
    EXPECT_EQ(d4.getMinute(), 2);
    EXPECT_EQ(d4.getStringDateTime(), "03/05/2001 02:02");

    //EXPECT_THROW(Date("2010/04/23 25:00"), BadDateFormat);
}*/

/*TEST(test, likeSystem){
    PublicStream s1("lolzadaAllDay","PT_PT",12);
    Viewer v1("Rui","xXBoasXx",Date(2000,1,1));
    Viewer v2("Jorge","---___---",Date(2000,1,1));

    EXPECT_THROW(v1.giveFeedBack(like), NotInStreamException);

    v1.joinStream(&s1);
    v1.giveFeedBack(like);
    EXPECT_EQ(s1.getLikes(),1);
    EXPECT_EQ(s1.getDislikes(),0);

    v1.giveFeedBack(like);
    EXPECT_EQ(s1.getLikes(),1);
    EXPECT_EQ(s1.getDislikes(),0);

    v2.joinStream(&s1);
    v2.giveFeedBack(like);
    EXPECT_EQ(s1.getLikes(),2);
    EXPECT_EQ(s1.getDislikes(),0);

    v2.giveFeedBack(dislike);
    EXPECT_EQ(s1.getLikes(),1);
    EXPECT_EQ(s1.getDislikes(),1);

    v2.leaveStream();
    EXPECT_EQ(s1.getLikes(),1);
    EXPECT_EQ(s1.getDislikes(),1);
    EXPECT_THROW(v2.giveFeedBack(like), NotInStreamException);

    v1.giveFeedBack(none);
    EXPECT_EQ(s1.getLikes(),0);
    EXPECT_EQ(s1.getDislikes(),1);
}*/

/*TEST(test, commentSystem) {
    PublicStream s1("lolzadaAllDay", "PT_PT", 12);
    PrivateStream s2("pum pum tiros e porrada", "EN", 20);
    Viewer v1("Rui", "xXBoasXx", Date(2000, 1, 1));
    Viewer v2("Jorge", "---___---", Date(1980, 1, 1));

    v1.joinStream(&s1);
    EXPECT_THROW(v1.giveFeedBack("muito boa streamer"),NotPrivateStreamException);

    s2.addValidUser(&v2);
    v2.joinStream(&s2);
    v2.giveFeedBack(like);
    EXPECT_EQ(s2.getLikes(),1);
    EXPECT_EQ(s2.getDislikes(),0);

    v2.giveFeedBack("meu deus topzana!!!!!!!!!!!!!!! <3 ");
    EXPECT_EQ(s2.getNumberComments(),1);
    std::cout << s1.getInfo() << std::endl;
    std::cout << s2.getInfo();

}*/


TEST(test, dataBase){

    /*
    PublicStream *s1 = new PublicStream("Stream 1", PT_PT, gaming);
    PublicStream *s2 = new PublicStream("Stream 2", PT_BR, technology);
    PublicStream *s3 = new PublicStream("Ok 1", PT_PT, cooking);
    PublicStream *s4 = new PublicStream("S", PT_PT, music);
    PublicStream *s5 = new PublicStream("S5", PT_PT, meetGreet);
*/




/*
    StreamZ streamZ;
    streamZ.init();
    streamZ.run();
    streamZ.getUserM()->createViewer("Rui", "user1", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Rui", "user2", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Rui", "user3", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Rui", "user4", Date(2000, 1, 1));

    ASSERT_EQ(streamZ.getSearchM()->getUser("user1")->getName(), "Rui");
    ASSERT_THROW(streamZ.getUserM()->createViewer("Rui", "user1", Date(2001, 1, 1)),
                  AlreadyExists<std::string>);
*/
}

/*
TEST(test, testSorts){

    StreamZ streamZ;
    streamZ.init();
    streamZ.run();

    streamZ.getUserM()->createViewer("Rui", "UsEr1", Date(2000, 1, 1));
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    streamZ.getUserM()->createViewer("Rui", "USER2", Date(2000, 1, 1));
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    streamZ.getUserM()->createViewer("Rui", "user3", Date(2000, 1, 1));
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    streamZ.getUserM()->createViewer("Rui", "user4", Date(2000, 1, 1));


    streamZ.getStreamManager()->createPublicStream("Stream 1", PT_PT, gaming);
    streamZ.getStreamManager()->createPublicStream("Stream 2", PT_BR, technology);
    streamZ.getStreamManager()->createPublicStream("Ok 1", PT_PT, cooking);
    streamZ.getStreamManager()->createPublicStream("S", PT_PT, music);
    streamZ.getStreamManager()->createPublicStream("S5", PT_PT, meetGreet);

    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->joinStream(
            dynamic_cast<LiveStream *>(streamZ.getSearchM()->getStream(0))
            );
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user2"))->joinStream(
            dynamic_cast<LiveStream *>(streamZ.getSearchM()->getStream(0))
    );
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user3"))->joinStream(
            dynamic_cast<LiveStream *>(streamZ.getSearchM()->getStream(1))
    );
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->joinStream(
            dynamic_cast<LiveStream *>(streamZ.getSearchM()->getStream(2))
    );

    std::vector<LiveStream *> streams;
    streamZ.getSortM()->sortStreamByViews(streams);
    ASSERT_EQ(streams[0]->getTitle(),"Stream 1");
    ASSERT_EQ(streams[0]->getNumViewers(), 2);
    ASSERT_EQ(streams[1]->getNumViewers(), 1);
    ASSERT_EQ(streams[2]->getNumViewers(), 1);
    streamZ.getSortM()->sortStreamByViews(streams, true);
    ASSERT_EQ(streams[4]->getTitle(),"Stream 1");
    ASSERT_EQ(streams[4]->getNumViewers(), 2);
    ASSERT_EQ(streams[3]->getNumViewers(), 1);
    ASSERT_EQ(streams[2]->getNumViewers(), 1);
    ASSERT_EQ(streams[0]->getNumViewers(), 0);

    std::vector<User *> users;
    streamZ.getSortM()->sortUserDatePlatform(users);
    ASSERT_EQ(users[0]->getNickName(), "user1");
    ASSERT_EQ(users[1]->getNickName(), "user2");
    ASSERT_EQ(users[2]->getNickName(), "user3");
    ASSERT_EQ(users[3]->getNickName(), "user4");

    std::vector<genre> _genres =  {gaming, technology, cooking};
    streamZ.getSearchM()->listLiveStreams(streams, "", _genres);
    streamZ.getSortM()->sortStreamByViews(streams);
    ASSERT_EQ(streams[0]->getTitle(), "Stream 1");
}
*/


TEST(test, adminOps){
    StreamZ streamZ;
    streamZ.init();

    streamZ.getUserM()->createViewer("Rui", "UsEr1","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Jacinto", "USER2","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Luis", "user3","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Alfredo", "user4","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe", "user5","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe 2", "user6","random", Date(2000, 1, 1));

    streamZ.getUserM()->createStreamer("Streamer 1", "streamer1","random", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 2", "streamer2","random", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer3","random", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer4","random", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer5","random", Date(1995, 2,3));

    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer1"))->startPublicStream("Stream 1", PT_PT, gaming);
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer2"))->startPublicStream("Stream 2", PT_BR, technology);
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer3"))->startPublicStream("Ok 1", PT_PT, cooking);
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer4"))->startPublicStream("S", PT_PT, music);
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer5"))->startPublicStream("S5", SPA, meetGreet);

    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->joinStream(2);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user2"))->joinStream(1);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user3"))->joinStream(2);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->joinStream(2);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user5"))->joinStream(4);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user6"))->joinStream(3);

    ASSERT_EQ(streamZ.getAdminOps()->rankViewsLang(), PT_BR);
    ASSERT_EQ(streamZ.getAdminOps()->rankViewsLang(true), SPA);
    ASSERT_EQ(streamZ.getAdminOps()->rankViewsGenres(), technology);
    ASSERT_EQ(streamZ.getAdminOps()->rankViewsGenres(true), meetGreet);

    ASSERT_EQ(streamZ.getAdminOps()->numStreamsAll(), 5);

    ASSERT_EQ(streamZ.getAdminOps()->numStreams(false), 0);
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer1"))->closeStream();
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer2"))->closeStream();
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer3"))->closeStream();
    ASSERT_EQ(streamZ.getAdminOps()->numStreams(false), 3);
    ASSERT_EQ(dynamic_cast<Viewer*>(streamZ.getSearchM()->getUser("user1"))->watching(), false);
    dynamic_cast<Viewer*>(streamZ.getSearchM()->getUser("user1"))->joinStream(4);

    float val = streamZ.getAdminOps()->medianViewsStream();
    std::stringstream ss;
    ss << val;
    ASSERT_EQ(ss.str(), "1.4");
    ASSERT_EQ(streamZ.getAdminOps()->numStreams(), 2);
}

TEST(test, likeSystem){
    StreamZ streamZ;
    streamZ.init();
    //streamZ.run();

    streamZ.getUserM()->createViewer("Rui", "UsEr1","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Jacinto", "USER2","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Luis", "user3","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Alfredo", "user4","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe", "user5","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe 2", "user6","random", Date(2000, 1, 1));

    streamZ.getUserM()->createStreamer("Streamer 1", "streamer1","random", Date(1995, 2,3));

    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer1"))->startPublicStream("Stream 1", PT_PT, gaming);

    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->joinStream(1);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user2"))->joinStream(1);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user3"))->joinStream(1);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->joinStream(1);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user5"))->joinStream(1);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user6"))->joinStream(1);

    ASSERT_EQ(dynamic_cast<LiveStream * >(streamZ.getSearchM()->getStream(1))->getNumViewers(),6);
    ASSERT_EQ(dynamic_cast<LiveStream * >(streamZ.getSearchM()->getStream(1))->getDislikes(),0);
    ASSERT_EQ(dynamic_cast<LiveStream * >(streamZ.getSearchM()->getStream(1))->getLikes(),0);

    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->giveFeedBack(like);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user2"))->giveFeedBack(dislike);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user3"))->giveFeedBack(like);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->giveFeedBack(like);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user5"))->giveFeedBack(dislike);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user6"))->giveFeedBack(like);

    ASSERT_EQ(dynamic_cast<LiveStream * >(streamZ.getSearchM()->getStream(1))->getDislikes(),2);
    ASSERT_EQ(dynamic_cast<LiveStream * >(streamZ.getSearchM()->getStream(1))->getLikes(),4);

    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user5"))->giveFeedBack(none);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user6"))->giveFeedBack(none);

    ASSERT_EQ(dynamic_cast<LiveStream * >(streamZ.getSearchM()->getStream(1))->getDislikes(),1);
    ASSERT_EQ(dynamic_cast<LiveStream * >(streamZ.getSearchM()->getStream(1))->getLikes(),3);

    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->leaveStream();
    ASSERT_EQ(dynamic_cast<LiveStream * >(streamZ.getSearchM()->getStream(1))->getLikes(),3);

    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->joinStream(1);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->giveFeedBack(like);
    ASSERT_EQ(dynamic_cast<LiveStream * >(streamZ.getSearchM()->getStream(1))->getLikes(),3);


}
TEST(test, testDestructs){
    StreamZ streamZ;
    streamZ.init();
    //streamZ.run();

    streamZ.getUserM()->createViewer("Rui", "UsEr1","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Jacinto", "USER2","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Luis", "user3","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Alfredo", "user4","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe", "user5","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe 2", "user6","random", Date(2000, 1, 1));

    streamZ.getUserM()->createStreamer("Streamer 1", "streamer1","random", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 2", "streamer2","random", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer3","random", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer4","random", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer5","random", Date(1995, 2,3));

    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer1"))->startPublicStream("Stream 1", PT_PT, gaming);
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer2"))->startPublicStream("Stream 2", PT_BR, technology);
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer3"))->startPublicStream("Ok 1", PT_PT, cooking);
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer4"))->startPublicStream("S", PT_PT, music);
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer5"))->startPublicStream("S5", SPA, meetGreet);

    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->joinStream(2);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user2"))->joinStream(1);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user3"))->joinStream(2);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->joinStream(2);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user5"))->joinStream(4);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user6"))->joinStream(3);

    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->followStreamer("streamer2");
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user2"))->followStreamer("streamer2");
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user3"))->followStreamer("streamer1");

    ASSERT_EQ(dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer2"))->getNumFollowers(), 2);

    ASSERT_EQ(dynamic_cast<LiveStream *>(streamZ.getSearchM()->getStream(2))->getNumViewers(), 3);
    streamZ.getUserM()->removeUser("streamer1");
    ASSERT_THROW(streamZ.getSearchM()->getStream(1), DoesNotExist<ID>);
    ASSERT_EQ(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user2"))->watching(), false);
    streamZ.getUserM()->removeUser("user1");

    ASSERT_EQ(dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer2"))->getNumFollowers(), 1);

    ASSERT_EQ(dynamic_cast<LiveStream *>(streamZ.getSearchM()->getStream(2))->getNumViewers(), 2);
    streamZ.getStreamManager()->removeStream(2);
    ASSERT_EQ(dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer2"))->streaming(), false);
    ASSERT_EQ(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user3"))->watching(), false);
    ASSERT_EQ(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user3"))->isInStreamHistory(2), false);
    ASSERT_EQ(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->watching(), false);
    ASSERT_THROW(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->watching(), DoesNotExist<std::string>);
    ASSERT_THROW(dynamic_cast<Viewer *>(streamZ.getSearchM()->getStream(2)), DoesNotExist<ID>);

    streamZ.getUserM()->createViewer("Ganda cringe 2", "user7","random", Date(2000, 1, 1));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer6","random", Date(1995, 2,3));

    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer6"))->startPublicStream("S5", SPA, meetGreet);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user7"))->joinStream(6);
    ASSERT_EQ(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user7"))->getCurrWatching(), 6 );
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer6"))->closeStream();
    ASSERT_TRUE(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user7"))->isInStreamHistory(6));
    streamZ.getStreamManager()->removeStream(6);
    ASSERT_FALSE(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user7"))->isInStreamHistory(6));


}

TEST(test, files1){
    StreamZ streamZ;
    streamZ.init();
    streamZ.run();

    try{
        streamZ.getUserM()->createViewer("Rui", "UsEr1","random", Date(2000, 1, 1));
        streamZ.getUserM()->createViewer("Jacinto", "USER2","random", Date(2000, 1, 1));
        streamZ.getUserM()->createViewer("Luis", "user3","random", Date(2000, 1, 1));
        streamZ.getUserM()->createViewer("Alfredo", "user4","random", Date(2000, 1, 1));
        streamZ.getUserM()->createViewer("Ganda cringe", "user5","random", Date(2000, 1, 1));
        streamZ.getUserM()->createViewer("Ganda cringe 2", "user6","random", Date(2000, 1, 1));

        streamZ.getUserM()->createStreamer("Streamer 1", "streamer1","random", Date(1995, 2,3));
        streamZ.getUserM()->createStreamer("Streamer 2", "streamer2","random", Date(1995, 2,3));
        streamZ.getUserM()->createStreamer("Streamer 3", "streamer3","random", Date(1995, 2,3));
        streamZ.getUserM()->createStreamer("Streamer 3", "streamer4","random", Date(1995, 2,3));
        streamZ.getUserM()->createStreamer("Streamer 3", "streamer5","random", Date(1995, 2,3));

        dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer1"))->startPublicStream("Stream 1", PT_PT, gaming);
        dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer2"))->startPublicStream("Stream 2", PT_BR, technology);
        dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer3"))->startPublicStream("Ok 1", PT_PT, cooking);



        dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer4"))->startPrivateStream("S", PT_PT, music);
        dynamic_cast<PrivateStream *>(streamZ.getSearchM()->getStream(4))->addValidUser("user4");
        dynamic_cast<PrivateStream *>(streamZ.getSearchM()->getStream(4))->addValidUser("user5");
        dynamic_cast<PrivateStream *>(streamZ.getSearchM()->getStream(4))->addValidUser("user6");



        dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer5"))->startPrivateStream("S5", SPA, meetGreet);

        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->joinStream(2);
        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->giveFeedBack(like);
        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user2"))->joinStream(1);
        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user2"))->giveFeedBack(dislike);
        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user3"))->joinStream(2);
        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user3"))->giveFeedBack(dislike);
        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->joinStream(2);
        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->giveFeedBack(dislike);
        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user5"))->joinStream(4);

        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user5"))->giveFeedBack("Very cool");
        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user5"))->giveFeedBack("Very cool 2");
        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user6"))->joinStream(4);
        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user6"))->giveFeedBack("Fun streamer!");


        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->followStreamer("streamer2");
        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user2"))->followStreamer("streamer2");
        dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user3"))->followStreamer("streamer1");

        //dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer1"))->closeStream();
        //dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer2"))->closeStream();
        dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer3"))->closeStream();

        //dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer4"))->closeStream();
        //dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer5"))->closeStream();

    }
    catch (AlreadyExists<std::string> & e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    streamZ.shutdown("DB.txt");


    streamZ.init();
    streamZ.run();



    ASSERT_EQ(streamZ.getDatabase().getUsers().size(), 11);
    ASSERT_EQ(streamZ.getDatabase().getStreams().size(), 5);

    streamZ.getUserM()->createStreamer("Streamer 6", "streamer6","random", Date(1995, 2,3));
    streamZ.getAdminOps()->mostViewed();

    ASSERT_EQ(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->watching(), true);
    ASSERT_EQ(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user2"))->getCurrWatching(), 1);

    ASSERT_EQ(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->getCurrWatching(), 2);
    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->leaveStream();


    ASSERT_EQ(dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer1"))->streaming(), true);
    ASSERT_EQ(dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer1"))->getNumFollowers(), 1);
    ASSERT_EQ(dynamic_cast<PublicStream *>(streamZ.getSearchM()->getStream(2))->getLikes(), 1);
    ASSERT_EQ(dynamic_cast<PublicStream *>(streamZ.getSearchM()->getStream(2))->getDislikes(), 2);
    ASSERT_EQ(dynamic_cast<Stream *>(streamZ.getSearchM()->getStream(3))->getStreamState(), finished);

    ASSERT_EQ(dynamic_cast<PrivateStream *>(streamZ.getSearchM()->getStream(4))->getNumberComments(), 3);
    ASSERT_EQ(dynamic_cast<PrivateStream *>(streamZ.getSearchM()->getStream(4))->getNumViewers(), 2);

    dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->joinStream(4);

    ASSERT_EQ(dynamic_cast<PrivateStream *>(streamZ.getSearchM()->getStream(4))->getNumViewers(), 3);

    ASSERT_EQ(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->watching(), true);
    ASSERT_EQ(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user2"))->getCurrWatching(), 1);
    ASSERT_EQ(dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer1"))->streaming(), true);
    ASSERT_EQ(dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer1"))->getNumFollowers(), 1);

}

std::string randomChars(){
    std::string chars = " abcdefghijklmnopqrstuvwxyz";
    std::stringstream ss;
    int size = rand()%15;

    for (int i = 0; i < size; ++i) {
        ss << chars[rand()%chars.length()];
    }

    return ss.str();

}


void buildTestData(){

    StreamZ streamZ;
    streamZ.init();
    streamZ.run();

    streamZ.getUserM()->createAdmin("Super User", "admin_of_streamz", "super_strong_password", Date(1990, 12, 25));

    streamZ.getUserM()->createViewer("Rui", "UsEr1","pass1123", Date(1992, 2, 5));
    streamZ.getUserM()->createViewer("Jacinto", "USER2","raasdasd", Date(1980, 3, 9));
    streamZ.getUserM()->createViewer("Luis", "usEr3","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Alfredo", "user4","random", Date(2002, 6, 1));
    streamZ.getUserM()->createViewer("Brocolo", "user5","random", Date(2000, 2, 9));
    streamZ.getUserM()->createViewer("Alberto Martins", "user6","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Andre Julio Moreira", "watching_memes","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Rodado", "sir_sir","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Andre Pereira", "crocodile_crazy","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Nuno Alves", "idkwhat","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Andre 2", "clear_head","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Rolando", "ronaldo","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Aleatoriamente valido com 6 nomes fixes", "music_finder","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer(" No name man", "cristiano","random", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Opa hello", "pedro1254","random", Date(2000, 1, 1));

    streamZ.getUserM()->createStreamer("Pewdipie", "streamer1","random", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Michael VSauce", "streamer2","random", Date(1995, 1,3));
    streamZ.getUserM()->createStreamer("AEFEUP", "streamer3","random", Date(1985, 2,6));
    streamZ.getUserM()->createStreamer("Nobody games", "streamer4","random", Date(2000, 7,20));
    streamZ.getUserM()->createStreamer("Fine talks", "streamer5","random", Date(1991, 8,29));
    streamZ.getUserM()->createStreamer("Gordon Ramsay Cooks", "streamer6","random", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Something", "whateve1r","random", Date(1971, 10,8));
    streamZ.getUserM()->createStreamer("Something 2", "whatever2","random", Date(1971, 10,8));
    streamZ.getUserM()->createStreamer("Something 3", "something","random", Date(1971, 10,8));
    streamZ.getUserM()->createStreamer("Crazy man", "crazy_games","random", Date(1971, 10,8));
    streamZ.getUserM()->createStreamer("Something 6", "its_fine_dude","random", Date(1971, 10,8));
    streamZ.getUserM()->createStreamer("Something Seven times big name", "its_not_fine_dude","random", Date(1971, 10,8));

    SearchManager * sm = streamZ.getSearchM();

    dynamic_cast<Streamer *>( sm->getUser("streamer1"))->startPublicStream("First stream", PT_PT, meetGreet);

    dynamic_cast<Viewer *>( sm->getUser("user1"))->joinStream(1);
    dynamic_cast<Viewer *>( sm->getUser("user2"))->joinStream(1);
    dynamic_cast<Viewer *>( sm->getUser("user3"))->joinStream(1);
    dynamic_cast<Viewer *>( sm->getUser("user4"))->joinStream(1);

    dynamic_cast<Streamer *>( sm->getUser("streamer1"))->closeStream();



    dynamic_cast<Streamer *>( sm->getUser("whateve1r"))->startPrivateStream("Jamming to the vibe", ENG, music);
    ID id1 = dynamic_cast<Streamer *>( sm->getUser("whateve1r"))->getStreamID();

    dynamic_cast<PrivateStream *>( sm->getStream(id1) )->addValidUser("crocodile_crazy");
    dynamic_cast<PrivateStream *>( sm->getStream(id1) )->addValidUser("clear_head");
    dynamic_cast<PrivateStream *>( sm->getStream(id1) )->addValidUser("user2");
    dynamic_cast<PrivateStream *>( sm->getStream(id1) )->addValidUser("user1");
    dynamic_cast<PrivateStream *>( sm->getStream(id1) )->addValidUser("ronaldo");

    dynamic_cast<Viewer *>( sm->getUser("crocodile_crazy"))->joinStream(id1);
    dynamic_cast<Viewer *>( sm->getUser("clear_head"))->joinStream(id1);
    dynamic_cast<Viewer *>( sm->getUser("USER2"))->joinStream(id1);
    dynamic_cast<Viewer *>( sm->getUser("UsEr1"))->joinStream(id1);

    dynamic_cast<Streamer *>( sm->getUser("whatever2"))->startPrivateStream("Give away stream", GER, technology);
    ID id2 = dynamic_cast<Streamer *>( sm->getUser("whatever2"))->getStreamID();

    dynamic_cast<PrivateStream *>( sm->getStream(id2) )->addValidUser("crocodile_crazy");
    dynamic_cast<PrivateStream *>( sm->getStream(id2) )->addValidUser("clear_head");
    dynamic_cast<PrivateStream *>( sm->getStream(id2) )->addValidUser("user4");
    dynamic_cast<PrivateStream *>( sm->getStream(id2) )->addValidUser("user3");
    dynamic_cast<PrivateStream *>( sm->getStream(id2) )->addValidUser("user1");
    dynamic_cast<PrivateStream *>( sm->getStream(id2) )->addValidUser("user6");
    dynamic_cast<PrivateStream *>( sm->getStream(id2) )->addValidUser("watching_memes");
    dynamic_cast<PrivateStream *>( sm->getStream(id2) )->addValidUser("sir_sir");
    dynamic_cast<PrivateStream *>( sm->getStream(id2) )->addValidUser("idkwhat");
    dynamic_cast<PrivateStream *>( sm->getStream(id2) )->addValidUser("cristiano");
    dynamic_cast<PrivateStream *>( sm->getStream(id2) )->addValidUser("pedro1254");
    dynamic_cast<PrivateStream *>( sm->getStream(id2) )->addValidUser("ronaldo");


    dynamic_cast<Viewer *>( sm->getUser("user3"))->joinStream(id2);
    dynamic_cast<Viewer *>( sm->getUser("user4"))->joinStream(id2);
    dynamic_cast<Viewer *>( sm->getUser("ronaldo"))->joinStream(id2);
    dynamic_cast<Viewer *>( sm->getUser("user6"))->joinStream(id2);
    dynamic_cast<Viewer *>( sm->getUser("watching_memes"))->joinStream(id2);
    dynamic_cast<Viewer *>( sm->getUser("sir_sir"))->joinStream(id2);
    dynamic_cast<Viewer *>( sm->getUser("idkwhat"))->joinStream(id2);
    dynamic_cast<Viewer *>( sm->getUser("cristiano"))->joinStream(id2);
    dynamic_cast<Viewer *>( sm->getUser("pedro1254"))->joinStream(id2);


    dynamic_cast<Streamer *>( sm->getUser("streamer2"))->startPublicStream("Second stream - Minecraft", PT_PT, gaming);
    ID id3 = dynamic_cast<Streamer *>( sm->getUser("streamer2"))->getStreamID();

    for (int i = 0; i < 20; ++i) {
        streamZ.getUserM()->createViewer("New name " + std::to_string(i), "new_user_" + std::to_string(i),"pass1123", Date(1992, 2, 5));
        dynamic_cast<Viewer *>( sm->getUser("new_user_" + std::to_string(i)))->joinStream(id3);
    }

    for (int i = 0; i < 5; ++i) {
        dynamic_cast<Viewer *>( sm->getUser("new_user_" + std::to_string(i)))->leaveStream();
    }

    dynamic_cast<Streamer *>( sm->getUser("streamer3"))->startPublicStream("Second stream - Minecraft", PT_PT, gaming);
    ID id4 = dynamic_cast<Streamer *>( sm->getUser("streamer3"))->getStreamID();

    for (int i = 0; i < 5; ++i) {
        dynamic_cast<Viewer *>( sm->getUser("new_user_" + std::to_string(i)))->joinStream(id4);
    }

    for (int i = 20; i < 50; ++i) {
        streamZ.getUserM()->createViewer("New user " + std::to_string(i), "new_user_" + std::to_string(i),"pass1123", Date(1992, 2, 5));
        dynamic_cast<Viewer *>( sm->getUser("new_user_" + std::to_string(i)))->joinStream(id4);
    }

    for (int i = 0; i < 10; ++i) {
        dynamic_cast<Viewer *>( sm->getUser("new_user_" + std::to_string(i)))->leaveStream();
    }



    dynamic_cast<Streamer *>( sm->getUser("streamer4"))->startPublicStream("Cooking french fries", language::FRE, cooking);
    ID id5 = dynamic_cast<Streamer *>( sm->getUser("streamer4"))->getStreamID();

    for (int i = 0; i < 10; ++i) {
        dynamic_cast<Viewer *>( sm->getUser("new_user_" + std::to_string(i)))->joinStream(id5);
    }

    for (int i = 50; i < 90; ++i) {
        streamZ.getUserM()->createViewer("Cristiano Ronaldo " + std::to_string(i), "new_user_" + std::to_string(i),"pass1123", Date(1992, 2, 5));
        dynamic_cast<Viewer *>( sm->getUser("new_user_" + std::to_string(i)))->joinStream(id5);
    }

    for (int i = 55; i < 75; ++i) {
        dynamic_cast<Viewer *>( sm->getUser("new_user_" + std::to_string(i)))->leaveStream();
    }



    dynamic_cast<Streamer *>( sm->getUser("streamer5"))->startPublicStream("Russian cars", language::RUS, genre::technology);
    ID id6 = dynamic_cast<Streamer *>( sm->getUser("streamer5"))->getStreamID();


    for (int i = 55; i < 75; ++i) {
        dynamic_cast<Viewer *>( sm->getUser("new_user_" + std::to_string(i)))->joinStream(id6);
    }

    for (int i = 90; i < 120; ++i) {
        streamZ.getUserM()->createViewer("No name dude " + std::to_string(i), "new_user_" + std::to_string(i),"pass1123", Date(1992, 2, 5));
        dynamic_cast<Viewer *>( sm->getUser("new_user_" + std::to_string(i)))->joinStream(id6);
    }


    ///     GENERATING SOME KINDA RANDOM DATA


    srand(time(nullptr)); // Seed 0

    int numStreams = (rand() % 30) + 20;

    for (int i = 0; i < numStreams; ++i) {
        streamZ.getUserM()->createStreamer(randomChars(),
                                         "osvaldo" + std::to_string(i),"nopass",
                                         Date(rand()%(2000 - 1971)+1971,rand()%12+1, rand()%27+1));




        dynamic_cast<Streamer *>( sm->getUser("osvaldo" + std::to_string(i)))->
                startPublicStream(randomChars(), (language)(rand()%10+1),
                                  (genre)(rand()%6+1));
        ID currId = dynamic_cast<Streamer *>( sm->getUser("osvaldo" + std::to_string(i)))->getStreamID();

        int numViewers = rand()%40 + 10;
        double timesum = 0;
        std::cout << "NEW ITERATION" << std::endl;
        for (int j = 0; j < numViewers; ++j) {
            auto t1 = std::chrono::high_resolution_clock::now();

            streamZ.getUserM()->createViewer(randomChars(),
                                             "random_viewer_public" + std::to_string(i) + "_" + std::to_string(j),
                                             randomChars(),
                                             Date(rand()%(2000 - 1971)+1971,rand()%12+1, rand()%27+1));

            auto t2 = std::chrono::high_resolution_clock::now();
            double time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
            timesum += time;
            double avrg = timesum/(j+1);

            std::cout << "Size - " << streamZ.getDatabase().getUsers().size() << " -- Time - " <<
            time << "us -- Average - " << avrg << "us" << std::endl << std::endl;

            try{
                dynamic_cast<Viewer *>(
                        sm->getUser("random_viewer_public" + std::to_string(i) + "_" + std::to_string(j)))->
                        joinStream(currId);
            } catch (const RestrictedAgeException & e) {}

        }

    }

    std::cout << "ENDS HERE" << std::endl;

    numStreams = (rand() % 10) + 5;

    for (int i = 0; i < numStreams; ++i) {
        streamZ.getUserM()->createStreamer(randomChars(),
                                           "ramiro" + std::to_string(i),"nopass",
                                           Date(rand()%(2000 - 1971)+1971,rand()%12+1, rand()%27+1));

        int maxViewers = rand()%10 + 10;

        dynamic_cast<Streamer *>( sm->getUser("ramiro" + std::to_string(i)))->
                startPrivateStream(randomChars(), (language)(rand()%10+1),
                                  (genre)(rand()%6+1), maxViewers);
        ID currId = dynamic_cast<Streamer *>( sm->getUser("ramiro" + std::to_string(i)))->getStreamID();

        int numViewers = rand()%maxViewers;
        double timesum = 0;
        for (int j = 0; j < numViewers; ++j) {
            auto t1 = std::chrono::high_resolution_clock::now();

            streamZ.getUserM()->createViewer(randomChars(),
                                             "random_viewer_private" + std::to_string(i) + "_" + std::to_string(j),
                                             randomChars(),
                                             Date(rand()%(2000 - 1971)+1971,rand()%12+1, rand()%27+1));


            auto t2 = std::chrono::high_resolution_clock::now();
            double time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
            timesum += time;
            double avrg = timesum/(j+1);

            std::cout << "Size - " << streamZ.getDatabase().getUsers().size() << " -- Time - " <<
                      time << "us -- Average - " << avrg << "us" << std::endl << std::endl;

            dynamic_cast<PrivateStream *>(sm->getStream(currId))->
                addValidUser("random_viewer_private" + std::to_string(i) + "_" + std::to_string(j));

            try{
                dynamic_cast<Viewer *>( sm->getUser("random_viewer_private" + std::to_string(i) + "_" + std::to_string(j)))->joinStream(currId);
            } catch (const RestrictedAgeException & e) {}
            catch (const MaxViewersReach & e) {}
        }

    }

    // Finish some random streams

    numStreams = rand()%10+10;

    auto it1 = streamZ.getDatabase().getUsers().begin();
    auto it2 = streamZ.getDatabase().getUsers().end();

    for (int i = 0; i < numStreams; ++i) {
        if(it1->second->getUserType() == streamer && dynamic_cast<Streamer *>(it1->second)->streaming()){
            dynamic_cast<Streamer *>(it1->second)->closeStream();
        }
        it1++;
    }

    streamZ.shutdown("final_data.txt");

}


int main(int argc, char** argv) {

    buildTestData();

    //testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();


}