//
// Created by peng on 10/30/25.
//

#include <string>
#include <iostream>
#include "foo.h"

#include <cstring>

extern "C" {

    auto foo_add(int a, int b)-> int {
        return a + b;
    }

    struct Point {
        int x;
        int y;
        const char* name;
    };

    auto getPoint(int a, int b, const char* name)-> Point {
        constexpr size_t N = 100;
        char* p = new char[N];
        memset(p, 0, sizeof(char) * N);
        memcpy(p, name, N);

        auto s = std::string(name);
        std::cout << "getPoint is " << s << std::endl;
        return Point { a, b ,p};
    }

    auto freePersonInner(Point* a)-> void {
        std::cout << "freePersonInner is freeing" << std::endl;
        if (a != nullptr && a -> name != nullptr) {
            delete a -> name;
            a -> name = nullptr;
        }
    }
}
