#include <iostream>

#include "Stream.h"
#include <gtest/gtest.h>

using testing::Eq;

TEST(test, c_InserirAresta) {
    Stream porrada("Mortal combat porrada", "EN", 14);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}