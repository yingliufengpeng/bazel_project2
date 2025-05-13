//
// Created by peng on 5/13/25.
//

#include <pybind11/pybind11.h>
#include <iostream>
#include <strstream>

#include "pybind_numpy.h"

#include <pybind11/pybind11.h>

template <typename T>
class MySmartPtr {
public:
    MySmartPtr(T* ptr) : ptr_(ptr) {}
    ~MySmartPtr() { delete ptr_; }
    T* getPointer() const { return ptr_; }
private:
    T* ptr_;
};

// 声明持有者
PYBIND11_DECLARE_HOLDER_TYPE(T, MySmartPtr<T>);

// 特化 holder_helper
namespace pybind11 { namespace detail {
    template <typename T>
    struct holder_helper<MySmartPtr<T>> {
        static const T *get(const MySmartPtr<T> &p) { return p.getPointer(); }
    };
}}

// 示例类
class Person {
public:
    int value;
    Person(int v) : value(v) {}
};



void InitCustomSmallPointer(pybind11::module &m) {

    pybind11::class_<Person, MySmartPtr<Person>>(m, "Person")
            .def(pybind11::init<int>())
            .def_readwrite("value", &Person::value);


}
