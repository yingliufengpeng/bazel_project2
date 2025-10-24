//
// Created by peng on 24/10/2025.
//

#ifndef MAIN_EXTEND_H
#define MAIN_EXTEND_H
#include <iostream>

#include "MyContainer.h"

template <int n>
struct ForcedUnroll {
    template <typename Func, typename... Args>
    void operator()(const Func& f, Args... args) const {
        ForcedUnroll<n - 1>{}(f, args...);
        f(std::integral_constant<int, n - 1>{}, args...);
    }
};

template <>
struct ForcedUnroll<1> {
    template <typename Func, typename... Args>
    void operator()(const Func& f, Args... args) const {
        f(std::integral_constant<int, 0>{}, args...);
    }
};
void ff2();
inline void ff1() {
    std::cout << "ff1" << std::endl;

    auto r = ForcedUnroll<4>();
    auto f = [](int index, int s, int e) -> int {
        std::cout << "index " << index <<" s = " << s << " end is " << e << std::endl;
        return index + 1;
    };

    r(f, 1, 20);

    ff2();
}

inline void ff2() {
    std::cout << "ff2" << std::endl;

    MyContainer<int> container(5);

    // 初始化容器
    for (size_t i = 0; i < container.size(); ++i)
        container[i] = static_cast<int>(i * 10);

    // 使用自定义迭代器遍历
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;




}


#endif //MAIN_EXTEND_H
