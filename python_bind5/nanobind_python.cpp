#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
// #include <nanobind/stl/vector.h>
#include <nanobind/make_iterator.h> // Include for make_iterator

#include <Python.h>

#include <iostream>
#include <vector>

#include "lib/demo_type.h"

namespace nb = nanobind;


void init(PyObject* m) {
    PyInit_demo(m);
}

NB_MODULE(basic, m) {
    init(m.ptr());

    m.def("hello", []() { return "basic module ready"; });

}



