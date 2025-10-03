//
// Created by peng on 15/5/2025.
//
#include "third_party/my_lib/my_header.h"

#include <iostream>
#include <memory>
#include <vector>

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



namespace A {

template <typename F>
struct Age {
    template <typename... Args>
    inline F& apply() {
        return self();
    }

    template <typename T >
    F& operator()(T&& a) {
        std::cout << "Age  a is " << a << std::endl;
        return self();
    }

    constexpr bool short_circuit() const {
            return false;
     }
    template <typename T>
    void operator()(const std::vector<T>&& args) {
        for (const auto& arg : args) {
            self()(arg);
            if (self().short_circuit())
                return;
        }
    }
    template <typename T, typename... Args>
    inline F& apply(T&& arg, Args&&... args) {
            self()(std::forward<T>(arg));
            if (self().short_circuit()) {
                return self();
            } else {
                return apply(std::forward<Args>(args)...);
            }
        }


    private:
        inline F& self() {
            return *static_cast<F*>(this);
        }

    };


    struct CusAge : Age<CusAge> {

    };
}

struct FooImpl: T::Foo<FooImpl> {};
// struct FooImpl2: T::Foo<FooImpl2> {};


void test() {
    auto m = A::CusAge();
    m(3 );
    m.apply(34, 46);
}

int main() {
    test();
    std::cout << "3 + 4 = "  << add(3, 4) << std::endl;
    add(3, 4);

    auto b = fn<std::string, int>(43);
    std::cout << b << std::endl;

    auto c = T::createDeriveT();

    return 0;
}