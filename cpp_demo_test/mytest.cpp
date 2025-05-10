//
// Created by peng on 5/9/25.
//
#include <gtest/gtest.h>
// #include "../src/math.h"
#include "cpp_demo/src/Animal.h"

TEST(CppDemoTest, HelloTest) {
    // EXPECT_EQ(2, add(1, 1));
    // EXPECT_EQ(5, add(2, 3));
    auto animal = Animal("44");
    animal.sayHello();

    EXPECT_EQ(animal.get_value(), 4);
}



TEST(CppDemoTest, HelloTest2) {
    // EXPECT_EQ(2, add(1, 1));
    // EXPECT_EQ(5, add(2, 3));
    auto animal = Animal("44");
    animal.sayHello();

    EXPECT_EQ(animal.get_value(), 41);
}
