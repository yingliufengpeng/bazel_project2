//
// Created by peng on 5/11/25.
//
#include <gtest/gtest.h>
#include "Pet.h"


TEST(PetTest, HelloTest) {
    auto pet = Pet("name");
    auto i = 3;
    EXPECT_EQ(pet.name, "name");
}



TEST(PetTest, HelloTest2) {

}