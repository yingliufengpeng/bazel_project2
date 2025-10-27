//
// Created by peng on 2025/10/27.
//

#include <functional>
#include <iostream>
#include <memory>
#include <fmt/format.h>

#define VARIABLE(n, ...) int n;
#define INIT_VARIABLE(n, init) this -> n = (init);

#define PRINT_IMPL(n, u) ((u).n)
#define PRINT(n, u) os << PRINT_IMPL(n, u) << "," ;


auto add_context(std::string&& a, std::string&& b = "") -> void {
    std::cout << "error : " << a << ", " << b;
}




#define MULTI_VARIABLE(_, ...) \
_(CPU_INDEX, __VA_ARGS__) \
_(GPU_INDEX, __VA_ARGS__)

#define TORCH_RETHROW(e, ...)               \
do {                                        \
    add_context(__VA_ARGS__);               \
    throw std::runtime_error(                \
    std::string(#e) + "--" + fmt::format(__VA_ARGS__)); \
} while (false)

struct User {
    int id;
    int age;
    MULTI_VARIABLE(VARIABLE)

    explicit User() {
        id = age = 0;
        MULTI_VARIABLE(INIT_VARIABLE, 10)
    }

    ~User() {
        std::cout << "~User()" << std::endl;
        age = 0;
    }
};

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "{";
    os << user.id << ", ";
    os << user.age << ", ";

    MULTI_VARIABLE(PRINT, user)
    os << "}";
    return os;
}

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
        std::cout << "p is " << *p << std::endl;
        return a + b + p -> age;
    };

    vec.push_back(m);
    vec.push_back(m2);
}

struct Person {
    int i;
    int j;
    std::string name;
    Person() = default;

    Person(int i, int j, std::string&& name = ""): i(i), j(j), name(std::move(name)) {}

    Person(Person& p) = default;

    Person(Person&& p) noexcept {
        std::cout << "Person&& is processing" << std::endl;
        i = p.i;
        j = p.j;
        name = std::move(p.name);
    };


    Person& operator=(Person& p) = default;
    Person& operator=(Person&& p) noexcept {
        i = p.i;
        j = p.j;
        name = std::move(p.name);
        return *this;
    };


};

auto make_person() -> Person {
    auto p = Person(1, 2, "aa");
    return std::move(p);
}


std::ostream& operator<<(std::ostream& os, const Person& person) {

    auto s = fmt::format("{}, {}, {}", person.i, person.j, person.name);
    os << "{";
    os << s;
    os << "}";
    return os;
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
    add_context("ll");
    add_context("aa", "bb");

    try {
        TORCH_RETHROW("memory error", " role: system ", " action: delete ");

    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }



    auto p = Person(3, 4, "ok");
    std::cout << p << std::endl;

    auto p2 = Person(3, 4, "ok2");
    std::cout << p2 << std::endl;


    auto p3 = p2;
    std::cout << p3 << std::endl;
    std::cout << p2 << std::endl;


    p3 = Person(3, 4, "ok3");
    std::cout << p3 << std::endl;

    std::cout << "p4 is processing" << std::endl;
    auto p4 = make_person();
    std::cout << p4 << std::endl;

    std::cout << "p5 is processing" << std::endl;
    auto p5 = std::move(p4);
    std::cout << p5 << std::endl;
    std::cout << p4 << std::endl;

    std::cout << "= is processing" << std::endl;

    p4 = std::move(p5);
    std::cout << p4 << std::endl;
    std::cout << p5 << std::endl;

}