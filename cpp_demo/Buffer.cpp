//
// Created by peng on 2025/10/25.
//

#include "Buffer.h"
using namespace peng;

// 构造函数
Buffer::Buffer(size_t size)
    : size_(size), data_(new char[size]) {
    std::cout << "Constructed: " << size_ << " bytes" << std::endl;
}

Buffer::Buffer(const Buffer& other)
            : size_(other.size_), data_(new char[other.size_]) {
    std::memcpy(data_, other.data_, size_);
    std::cout << "Copy constructed" << std::endl;
}

Buffer& Buffer::operator=(const Buffer& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        data_ = new char[size_];
        std::memcpy(data_, other.data_, size_);
        std::cout << "Copy assigned" << std::endl;
    }
    return *this;
}


// 移动构造
Buffer::Buffer(Buffer&& other) noexcept
    : data_(other.data_), size_(other.size_) {
    other.data_ = nullptr;  // 把资源“偷走”
    other.size_ = 0;
    std::cout << "Move constructed" << std::endl;
}

Buffer& Buffer::operator=(Buffer&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr; // 清空源对象
        other.size_ = 0;
        std::cout << "Move assigned" << std::endl;
    }
    return *this;
}