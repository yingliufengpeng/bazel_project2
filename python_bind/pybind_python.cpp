#include <pybind11/pybind11.h>
#include <iostream>
#include "basic.h"
namespace py = pybind11;
PYBIND11_MODULE(basic, module) {
    module.doc() = "A basic pybind11 extension";
    module.def("add", &add, "A function that adds two numbers");
    module.attr("the_answer") = 42;
    py::object world = py::cast("World");
    module.attr("world") = world;
}