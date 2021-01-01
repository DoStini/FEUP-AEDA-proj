#include<iostream>
#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "Viewer.h"
#include "Date.h"
#include "PrivateStream.h"
#include "PublicStream.h"
#include "OrdersEmptyException.h"
#include "OrdersFullException.h"
#include "NoSuchOrderException.h"
#include "StreamZ.h"


using testing::Eq;

/*TEST(test, createUsers){

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
}*/

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

TEST(test, createDateString){
    Date d1 = Date("2001/05/23");
    EXPECT_EQ(d1.getYear(), 2001);
    EXPECT_EQ(d1.getMonth(), 5);
    EXPECT_EQ(d1.getDay(), 23);

    EXPECT_THROW(Date("2019/02/29"), BadDateFormat);
    EXPECT_THROW(Date("2019/02/29"), BadDateFormat);

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
}

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

    ASSERT_EQ((streamZ.getAdminOps()->rankViewsLang()), PT_BR);
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
    streamZ.run();
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
/*
TEST(test, files1){
    StreamZ streamZ;
    streamZ.init();
    //streamZ.run();

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
*/

TEST(test, run) {
    StreamZ streamZ = StreamZ();
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


    streamZ.getUserM()->createAdmin("Admin","admin", "admin",Date(2001, 02, 25));
    streamZ.getUserM()->createViewer("NUno","nuno", "nuno", Date(2001, 02, 25));
    streamZ.getUserM()->createViewer("roger","roger", "roger", Date(2001, 02, 25));
    streamZ.getUserM()->createViewer("asd","asd", "asd", Date(2001, 02, 25));
    streamZ.getUserM()->createStreamer("asd", "streamer", "streamer", Date(2001, 02, 25));

    reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("nuno"))->orderMerch("streamer",3,2);
    reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("nuno"))->orderMerch("streamer",3,3);
    reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("asd"))->orderMerch("streamer",2,2);
    reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("asd"))->orderMerch("streamer1",2,2);


    MerchandisingOrder merchandisingOrder = reinterpret_cast<Streamer*>(streamZ.getDatabase().getUsers().at("streamer"))->dispatchOrder();
    EXPECT_EQ(merchandisingOrder.getViewerName(), "asd");
    merchandisingOrder = reinterpret_cast<Streamer*>(streamZ.getDatabase().getUsers().at("streamer"))->dispatchOrder();
    EXPECT_EQ(merchandisingOrder.getViewerName(), "nuno");
    EXPECT_EQ(merchandisingOrder.getAvailability(), 3);
    merchandisingOrder = reinterpret_cast<Streamer*>(streamZ.getDatabase().getUsers().at("streamer"))->dispatchOrder();
    EXPECT_EQ(merchandisingOrder.getAvailability(), 2);

    EXPECT_THROW(reinterpret_cast<Streamer*>(streamZ.getDatabase().getUsers().at("streamer"))->dispatchOrder(), OrdersEmptyException);

    streamZ.getUserM()->setOrdersSize(5);

    reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("asd"))->orderMerch("streamer",2,2);
    reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("asd"))->orderMerch("streamer",2,2);
    reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("asd"))->orderMerch("streamer",2,2);
    reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("nuno"))->orderMerch("streamer",2,2);
    reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("asd"))->orderMerch("streamer",2,2);

    EXPECT_THROW(reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("asd"))->orderMerch("streamer",3,3), OrdersFullException);

    merchandisingOrder = reinterpret_cast<Streamer*>(streamZ.getDatabase().getUsers().at("streamer"))->dispatchOrder();
    EXPECT_EQ(merchandisingOrder.getAvailability(), 2);

    streamZ.getUserM()->removeUser("asd");

    merchandisingOrder = reinterpret_cast<Streamer*>(streamZ.getDatabase().getUsers().at("streamer"))->dispatchOrder();
    EXPECT_EQ(merchandisingOrder.getAvailability(), 2);
    EXPECT_THROW(reinterpret_cast<Streamer*>(streamZ.getDatabase().getUsers().at("streamer"))->dispatchOrder(), OrdersEmptyException);
    EXPECT_THROW(reinterpret_cast<Streamer*>(streamZ.getDatabase().getUsers().at("streamer1"))->dispatchOrder(), OrdersEmptyException);

    reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("nuno"))->orderMerch("streamer",2,0);
    reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("nuno"))->orderMerch("streamer",2,10);
    reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("nuno"))->orderMerch("streamer",2,3);

    merchandisingOrder = reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("nuno"))->removeOrder("streamer");
    EXPECT_EQ(merchandisingOrder.getAvailability(), 5);
    merchandisingOrder = reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("nuno"))->removeOrder("streamer");
    merchandisingOrder = reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("nuno"))->removeOrder("streamer");
    EXPECT_EQ(merchandisingOrder.getAvailability(), 1);
    EXPECT_THROW(reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("nuno"))->removeOrder("streamer"), NoSuchOrderException);
    EXPECT_THROW(reinterpret_cast<Viewer*>(streamZ.getDatabase().getUsers().at("nuno"))->removeOrder("asd"), DoesNotExist<std::string>);
    EXPECT_THROW(reinterpret_cast<Streamer*>(streamZ.getDatabase().getUsers().at("streamer"))->dispatchOrder(), OrdersEmptyException);


    //streamZ.run();
}

TEST(test, bst_donation) {
    StreamZ streamZ = StreamZ();
    streamZ.init();
    streamZ.getUserM()->createStreamer("falca","falca","123",Date(2001,1,3));
    streamZ.getUserM()->createStreamer("boas","boas","456",Date(2001,1,3));

    streamZ.getDonationManager()->creatDonation("falca",120,4);
    DonationItem found = streamZ.getDatabase().donations.findMax();
    EXPECT_EQ(found.getStreamerNick(), "falca");
    EXPECT_EQ(found.getAmount(), 120);
    EXPECT_EQ(found.getEvaluation(), 4);

    found = streamZ.getDatabase().donations.findMin();
    EXPECT_EQ(found.getStreamerNick(), "falca");
    EXPECT_EQ(found.getAmount(), 120);
    EXPECT_EQ(found.getEvaluation(), 4);


    streamZ.getDonationManager()->creatDonation("boas",250,3);

    found = streamZ.getDatabase().donations.findMax();
    EXPECT_EQ(found.getStreamerNick(), "boas");
    EXPECT_EQ(found.getAmount(), 250);
    EXPECT_EQ(found.getEvaluation(), 3);

    streamZ.getDonationManager()->creatDonation("boas",250,4);
    found = streamZ.getDatabase().donations.findMax();
    EXPECT_EQ(found.getStreamerNick(), "boas");
    EXPECT_EQ(found.getAmount(), 250);
    EXPECT_EQ(found.getEvaluation(), 4);

    vector<Donation*> vec;

    streamZ.getSearchM()->listDonations(vec);
    EXPECT_EQ(vec.size(), 3);

    streamZ.getSearchM()->listDonations(vec,vector<std::string>(),130);
    EXPECT_EQ(vec.size(), 2);

    streamZ.getSearchM()->listDonations(vec,vector<std::string>(),130,200);
    EXPECT_EQ(vec.size(), 0);

    vector<unsigned > eval;
    eval.push_back(4);
    streamZ.getSearchM()->listDonations(vec,vector<std::string>(),0,1000,eval);
    EXPECT_EQ(vec.size(), 2);

    vector<unsigned> eval2;
    eval2.push_back(1);
    streamZ.getSearchM()->listDonations(vec,vector<std::string>(),0,1000,eval2);
    EXPECT_EQ(vec.size(), 0);

    eval2.push_back(3);
    streamZ.getSearchM()->listDonations(vec,vector<std::string>(),0,1000,eval2);
    EXPECT_EQ(vec.size(), 1);

    streamZ.getDonationManager()->creatDonation("falca",130,4);
    streamZ.getDonationManager()->creatDonation("falca",135,4);
    streamZ.getDonationManager()->deleteAllDonationsByNick("boas");
    streamZ.getSearchM()->listDonations(vec);
    EXPECT_EQ(vec.size(), 3);

    streamZ.getDonationManager()->deleteAllDonationsByNick("falca");
    streamZ.getSearchM()->listDonations(vec);
    EXPECT_EQ(vec.size(), 0);

}

int mainTests(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


int main() {
    //return mainTests();

    StreamZ streamZ;
    streamZ.init("final_data.txt");
    streamZ.run();

    streamZ.shutdown("final_data.txt");
}