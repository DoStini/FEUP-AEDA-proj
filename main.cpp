#include <iostream>
#include <gtest/gtest.h>

#include "Date.h"

using testing::Eq;

TEST(test, createDate){
    Date d1 = Date("2001/05/23");
    EXPECT_EQ(d1.getYear(), 2001);
    EXPECT_EQ(d1.getMonth(), 5);
    EXPECT_EQ(d1.getDay(), 23);

    Date d2 = Date("1899/05/23");
    EXPECT_EQ(d2.getYear(), 1899);

    Date d3 = Date();
    std::cout << d3.getYear() << "/";
    std::cout << d3.getMonth() << "/";
    std::cout << d3.getDay() << std::endl;
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}