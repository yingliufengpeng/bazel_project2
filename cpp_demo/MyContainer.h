//
// Created by peng on 24/10/2025.
//

#ifndef MYCONTAINER_H
#define MYCONTAINER_H
#include <iostream>
#include <cstddef> // for size_t

// 自定义容器
template <typename T>
struct  MyContainer {
private:
    T* data;
    size_t sz;

public:
    MyContainer(size_t n) : sz(n) {
        data = new T[n];
        for (size_t i = 0; i < n; ++i)
            data[i] = T(); // 默认初始化
    }

    ~MyContainer() {
        delete[] data;
    }

    size_t size() const { return sz; }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    // --------- 自定义迭代器 ---------
    struct Iterator {
    private:
        T* ptr;

    public:
        Iterator(T* p) : ptr(p) {}

        // 解引用
        T& operator*() { return *ptr; }

        // 前置++
        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        // 后置++
        Iterator operator++(int) {
            Iterator temp = *this;
            ++ptr;
            return temp;
        }

        // 比较
        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }

        bool operator==(const Iterator& other) const {
            return ptr == other.ptr;
        }
    };

    // 返回迭代器起点和终点
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + sz); }
};


#endif //MYCONTAINER_H
