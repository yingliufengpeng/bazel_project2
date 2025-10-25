//
// Created by peng on 2025/10/25.
//

#ifndef BAZEL_PROJECT2_BUFFER_H
#define BAZEL_PROJECT2_BUFFER_H


#include <iostream>
#include <cstring>

namespace peng {
    struct  Buffer {

        char* data_;
        size_t size_;

        Buffer(size_t);
        // 析构函数
        ~Buffer() {
            delete[] data_;
            std::cout << "Destroyed" << std::endl;
        }

        // 拷贝构造（深拷贝）
        Buffer(const Buffer& other);

        // 拷贝赋值
        Buffer& operator=(const Buffer& other);

        // 移动构造
        Buffer(Buffer&& other) noexcept;

        // 移动赋值
        Buffer& operator=(Buffer&& other) noexcept;

        size_t size() const { return size_; }
    };


}




#endif //BAZEL_PROJECT2_BUFFER_H