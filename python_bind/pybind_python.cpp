#include <pybind11/pybind11.h>
#include <iostream>
#include "basic.h"

PYBIND11_MODULE(pybind_basic, module) {
    module.doc() = "A basic pybind11 extension";
    module.def("add", &add, "A function that adds two numbers");
}