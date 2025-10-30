//
// Created by peng on 10/30/25.
//

#ifndef BAZEL_PROJECT2_FOO_H
#define BAZEL_PROJECT2_FOO_H

extern "C" {
    struct Point;
    auto foo_add(int a, int b)-> int;

    auto getPoint(int a, int b, const char* name)-> Point;

    auto freePersonInner(Point* a)-> void;
}


#endif //BAZEL_PROJECT2_FOO_H