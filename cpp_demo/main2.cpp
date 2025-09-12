//
// Created by peng on 15/5/2025.
//
#include "third_party/my_lib/my_header.h"

#include <iostream>

template <typename X, typename X2, typename Y>
auto fn(Y&& y) {
    return y;

}

int main() {
    std::cout << "3 + 4 = "  << add(3, 4) << std::endl;
    add(3, 4);

    auto b = fn<std::string, int>(43);
    std::cout << b << std::endl;

    return 0;
}