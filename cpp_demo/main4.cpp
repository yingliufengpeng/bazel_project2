//
// Created by peng on 2025/10/27.
//

#include <functional>
#include <iostream>

struct User {
    int id;
    int age;

    ~User() {
        std::cout << "~User()" << std::endl;
        age = 0;
    }
};

using F = auto (int, int) -> int;

auto push_func(std::vector<F*>& vec) {
    auto m = +[](int a, int b) -> int {
        return a + b;
    };
    vec.push_back(m);
}

auto push_func2(std::vector<std::function<F>>& vec) {
    auto m = [](int a, int b) -> int {
        return a + b;
    };
    auto p = std::make_shared<User>();
    p -> age = 4;

    auto m2 = [p](int a, int b) -> int {

        return a + b + p -> age;
    };

    vec.push_back(m);
    vec.push_back(m2);
}


auto main() -> int {

    std::vector<F*> vec;
    std::vector<std::function<F>> vec2;
    push_func(vec);
    push_func2(vec2);

    for (auto &f: vec) {
        std::cout << f(2, 4) << std::endl;
    }

    std::cout << "vec2 ..." << std::endl;
    for (auto &f: vec2) {
        std::cout << f(2, 4) << std::endl;
    }

    std::cout << "Hello World!\n";

}