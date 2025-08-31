//
// Created by peng on 31/8/2025.
//

#ifndef BAZEL_PROJECT2_XY_H
#define BAZEL_PROJECT2_XY_H

#include <iostream>
namespace XY {

    template<typename T>
    T& _Show(T&& a) {
        return a;
    }

    /** 一元折叠
     * (... op pack)      // 前置 fold
     *   (pack op ...)      // 后置 fold
     *
     *  二元折叠
     *  (init op ... op pack)   // 左折叠
     *  (pack op ... op init)   // 右折叠
     *
     *
     * @tparam Args
     * @param args
     */


    template <typename ...Args>
    void Show(Args&& ... args) {
        (std::cout << ... << _Show(args)) << "\n"; // 左折叠

    }



}

#endif //BAZEL_PROJECT2_XY_H
