//
// Created by peng on 15/5/2025.
//
#include "third_party/my_lib/my_header.h"

#include <iostream>
#include <memory>

template <typename X, typename X2, typename Y>
auto fn(Y&& y) {
    return y;

}

struct Obj {};

namespace T {
    std::unique_ptr<Obj> createDeriveT();
}

namespace T {
    template <typename DeriveT>
    struct Foo {

        explicit Foo() {
            std::cout << "Foo" << std::endl;
        }

        private:
            friend std::unique_ptr<Obj> createDeriveT() {
                auto a = std::make_unique<Obj>();
                return std::make_unique<Obj>();
            }

        };



}
auto createDeriveT() {
    return T::createDeriveT();
}


struct FooImpl: T::Foo<FooImpl> {};
// struct FooImpl2: T::Foo<FooImpl2> {};

int main() {
    std::cout << "3 + 4 = "  << add(3, 4) << std::endl;
    add(3, 4);

    auto b = fn<std::string, int>(43);
    std::cout << b << std::endl;

    auto c = T::createDeriveT();

    return 0;
}