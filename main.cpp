#include <iostream>
#include <gtest/gtest.h>

#include "Viewer.h"
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
    Viewer v1("Andre Moreira", "gordoMan", Date(9,3,1999));
    Viewer v2("Andre Moreira", "gordox2", Date(9,3,1999));
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
    Viewer v1("Andre Moreira", "gordoMan", Date(9,3,1999));
    Viewer v2("Andre Moreira", "gordox2", Date(9,3,1999));

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


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}