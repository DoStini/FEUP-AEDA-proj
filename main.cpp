#include <iostream>
#include <gtest/gtest.h>

#include "Date.h"

using testing::Eq;

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