#include <iostream>
#include <gtest/gtest.h>

#include "Viewer.h"

using testing::Eq;

TEST(test, createViewer){
    EXPECT_THROW(Viewer("Andre Moreira", "gordoMan", Date(9,3,2001)), RestrictedAgeException);
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
    }
}


TEST(test, c_InserirAresta) {
    Stream porrada("Mortal combat porrada", "EN", 14);

}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}