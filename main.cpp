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

    EXPECT_THROW(Viewer("Andre Moreira", "gordoMan", Date(2009,3,9)), RestrictedAgeException);
    try{
        Viewer v1("Andre Moreira", "gordoMan", Date(2009,3,9));
    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;

        if(strcmp(ex.what(), "Minimum age failed") != 0){
            auto *e = dynamic_cast<RestrictedAgeException *>(&ex);
            std::cout << *e << std::endl;
        }
    }

    EXPECT_THROW(Streamer("Andre Moreira", "gordoxgames", Date(2006,1,1)), RestrictedAgeException);

    Streamer sir("classy man", "classy-sir", Date(2001,1,1));
    std::cout << "JCL JOINED: " << sir.getJoinedPlatformDate().getStringDateTime() << std::endl;
    EXPECT_EQ(sir.getBirthDate().getStringDate(), "01/01/2001");
    EXPECT_EQ(sir.getName(), "classy man");
}

/*
TEST(test, publicStream) {
    PublicStream s1("Nice stream", PT_PT,gaming,"unknow",12);
    ASSERT_EQ(s1.getTitle(), "Nice stream");
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
    PublicStream sp("Nice open source stream", PT_PT,gaming,"unknow",12);
    PrivateStream s1("Nice stream", PT_PT,gaming,"unknow",12,5);
    ASSERT_EQ(s1.getTitle(), "Nice stream");
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
    EXPECT_THROW(v1.giveFeedBack("muito boa stream"),NotPrivateStreamException);

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

    streamZ.getUserM()->createViewer("Rui", "UsEr1", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Jacinto", "USER2", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Luis", "user3", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Alfredo", "user4", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe", "user5", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe 2", "user6", Date(2000, 1, 1));

    streamZ.getUserM()->createStreamer("Streamer 1", "streamer1", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 2", "streamer2", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer3", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer4", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer5", Date(1995, 2,3));

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

    ASSERT_EQ(streamZ.getAdminOps()->numStreams(finishedType), 0);
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer1"))->closeStream();
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer2"))->closeStream();
    dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer3"))->closeStream();
    ASSERT_EQ(streamZ.getAdminOps()->numStreams(finishedType), 3);
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

    streamZ.getUserM()->createViewer("Rui", "UsEr1", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Jacinto", "USER2", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Luis", "user3", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Alfredo", "user4", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe", "user5", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe 2", "user6", Date(2000, 1, 1));

    streamZ.getUserM()->createStreamer("Streamer 1", "streamer1", Date(1995, 2,3));

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

    streamZ.getUserM()->createViewer("Rui", "UsEr1", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Jacinto", "USER2", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Luis", "user3", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Alfredo", "user4", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe", "user5", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe 2", "user6", Date(2000, 1, 1));

    streamZ.getUserM()->createStreamer("Streamer 1", "streamer1", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 2", "streamer2", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer3", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer4", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer5", Date(1995, 2,3));

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
    ASSERT_EQ(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user4"))->watching(), false);
    ASSERT_THROW(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->watching(), DoesNotExist<std::string>);
    ASSERT_THROW(dynamic_cast<Viewer *>(streamZ.getSearchM()->getStream(2)), DoesNotExist<ID>);
}
/*
TEST(test, files1){
    StreamZ streamZ;
    streamZ.init();
    streamZ.run();

    streamZ.getUserM()->createViewer("Rui", "UsEr1", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Jacinto", "USER2", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Luis", "user3", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Alfredo", "user4", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe", "user5", Date(2000, 1, 1));
    streamZ.getUserM()->createViewer("Ganda cringe 2", "user6", Date(2000, 1, 1));

    streamZ.getUserM()->createStreamer("Streamer 1", "streamer1", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 2", "streamer2", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer3", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer4", Date(1995, 2,3));
    streamZ.getUserM()->createStreamer("Streamer 3", "streamer5", Date(1995, 2,3));

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


    streamZ.shutdown("DB.txt");

}
*/

TEST(test, files2){
    StreamZ streamZ;
    streamZ.init();
    streamZ.run();


    ASSERT_EQ(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user1"))->watching(), true);
    ASSERT_EQ(dynamic_cast<Viewer *>(streamZ.getSearchM()->getUser("user2"))->getCurrWatching(), 1);
    ASSERT_EQ(dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer1"))->streaming(), true);
    ASSERT_EQ(dynamic_cast<Streamer *>(streamZ.getSearchM()->getUser("streamer1"))->getNumFollowers(), 1);

    ASSERT_EQ(streamZ.getDatabase().getUsers().size(), 11);

}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
