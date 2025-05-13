//
// Created by peng on 5/13/25.
//
#include <pybind11/pybind11.h>
#include <iostream>
#include <strstream>

#include "pybind_numpy.h"

namespace py = pybind11;

struct Example2 {
    int i, j;
    Example2(int i, int j) : i(i), j(j) {
        std::cout << "Example2::i = " << i << ", j = " << j << " Created ..."  << std::endl;
    }
    ~Example2() {
        std::cout << "  Example " << i << " " << j << " Destroyed... " << std::endl;
    }
};

std::unique_ptr<Example2> create_example() {

    return std::make_unique<Example2>(4, 5);
}

class Child : public std::enable_shared_from_this<Child> {

public:
    void HelloWorld() {
        std::cout << "Child::HelloWorld" << std::endl;
    }

};


class Parent {
public:
    Parent() : child(std::make_shared<Child>()) { }
    Child *get_child() { return child.get(); }  /* Hint: ** DON'T DO THIS ** */
private:
    std::shared_ptr<Child> child;
};



void InitSmartPoint(pybind11::module& m) {

    py::class_<Example2>(m, "Example2");

    m.def("create_example", &create_example);

    py::class_<Child, std::shared_ptr<Child>>(m, "Child")
    .def("HelloWorld", &Child::HelloWorld)
    ;

    py::class_<Parent, std::shared_ptr<Parent>>(m, "Parent")
       .def(py::init<>())
       .def("get_child", &Parent::get_child);

}