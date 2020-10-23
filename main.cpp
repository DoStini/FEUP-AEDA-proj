#include <iostream>
#include <gtest/gtest.h>

#include "Viewer.h"
#include "Date.h"
#include "PrivateStream.h"
#include "PublicStream.h"
using testing::Eq;

TEST(test, createViewer){
    /*
    EXPECT_THROW(Viewer("Andre Moreira", "gordoMan", Date(9,3,2007)), RestrictedAgeException);
    try{
        Viewer v1("Andre Moreira", "gordoMan", Date(9,3,2001));
    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;

        if(strcmp(ex.what(), "Minimum age failed") != 0){
            auto *e = dynamic_cast<RestrictedAgeException *>(&ex);
            std::cout << *e << std::endl;
        }
        else if (strcmp(ex.what(), "Invalid date") != 0){

        }
    }*/
}


TEST(test, publicStream) {
    PublicStream s1("Nice stream", "PT");
    ASSERT_EQ(s1.getTitle(), "Nice stream");
    ASSERT_EQ(s1.getMinAge(), 13);
    ASSERT_EQ(s1.getNumViewers(), 0);
    Viewer v1("Andre Moreira", "gordoMan", Date(1999,3,9));
    Viewer v2("Andre Moreira", "gordox2", Date(1999,3,9));
    s1.addViewer((User *) &v1);
    ASSERT_EQ(s1.getNumViewers(), 1);
    s1.addViewer((User *) &v2);
    ASSERT_EQ(s1.getNumViewers(), 2);

}

TEST(test, user_private_stream) {
    PublicStream sp("Nice open source stream", "PT");
    PrivateStream s1("Nice stream", "PT");
    ASSERT_EQ(s1.getTitle(), "Nice stream");
    ASSERT_EQ(s1.getMinAge(), 13);
    ASSERT_EQ(s1.getNumViewers(), 0);
    Viewer v1("Andre Moreira", "gordoMan", Date(1999, 3, 9));
    Viewer v2("Andre Moreira", "gordox2", Date(1999, 3, 9));

    EXPECT_THROW(v1.joinStream(&s1), RestrictedStreamException);
    EXPECT_THROW(v2.joinStream(&s1), RestrictedStreamException);

    s1.addValidUser(&v1);
    v1.joinStream(&s1);
    EXPECT_EQ(s1.getNumViewers(), 1);

    try{
        v2.joinStream(&s1);
    } catch (std::exception & e) {
        if(strcmp(e.what(), "User not whitelisted"))
            std::cout << *( dynamic_cast<RestrictedStreamException *>(&e) ) << std::endl;
    }

    EXPECT_THROW(v1.joinStream(&sp), AlreadyInStreamException);

}




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
    int diff = d1.getYearDifference(d2);
    EXPECT_EQ(diff, 20);

    Date d3 = Date("2001/02/25");
    diff = d1.getYearDifference(d3);
    EXPECT_EQ(diff, 1);

    Date d8 = Date("2001/03/01");
    Date d9 = Date("2004/03/01");
    diff = d9.getYearDifference(d8);
    EXPECT_EQ(diff, 3);

    Date d7 = Date("2002/02/25");
    diff = d3.getYearDifference(d7);
    EXPECT_EQ(diff, 1);

    Date d4 = Date("2020/02/24");
    diff = d1.getYearDifference(d4);
    EXPECT_EQ(diff, 19);

    Date d5 = Date("2600/02/24");
    diff = d1.getYearDifference(d5);
    EXPECT_EQ(diff, 599);

    Date d6 = Date("2600/02/25");
    diff = d1.getYearDifference(d6);
    EXPECT_EQ(diff, 600);
}

TEST(test, hourMinute) {
    Date d1 = Date();
    std::cout << d1.getMinute() << std::endl;
    std::cout << d1.getHour() << std::endl;
    std::cout << d1.getStringTime() << std::endl;
    std::cout << d1.getStringDate() << std::endl;

    Date d3 = Date("2010/04/23 23:00");
    EXPECT_EQ(d3.getHour(), 23);

    Date d2 = Date(2001, 02, 25, 12, 3);
    EXPECT_EQ(d2.getStringTime(), "25/02/2001 12:03");

    //EXPECT_THROW(Date("2010/04/23 25:00"), BadDateFormat);
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}