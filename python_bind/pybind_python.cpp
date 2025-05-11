#include <pybind11/pybind11.h>
#include <iostream>
#include "basic.h"
#include "Pet.h"
#include "Dog.h"
#include "PolymorphhicPet.h"
namespace py = pybind11;


PYBIND11_MODULE(basic, module) {
    module.doc() = "A basic pybind11 extension";
    module.def("add", &add, "A function that adds two numbers");
    module.attr("the_answer") = 42;
    py::object world = py::cast("World");
    module.attr("world") = world;


    auto pet = py::class_<Pet>(module, "Pet", py::dynamic_attr())
      .def(py::init<const std::string &>())
      .def(py::init<const std::string &, Pet::Kind>())
      .def("setName", &Pet::setName)
      .def("getName", &Pet::getName)
      .def("show", &Pet::show)
    .def_readwrite("type", &Pet::type)
    .def_readwrite("attr", &Pet::attr)
      .def("__repr__", [](const Pet &a) {
          return "Pet {" + a.getName() + "}";
      })

    .def("set", py::overload_cast<int>(&Pet::set), "Set the pet's age")
    .def("set", py::overload_cast<const std::string &>(&Pet::set), "Set the pet's name")
    .def_readwrite("name", &Pet::name);

    py::enum_<Pet::Kind>(pet, "Kind")
    .value("Dog", Pet::Kind::Dog)
    .value("Cat", Pet::Kind::Cat)
    .export_values();

    py::class_<Pet::Attributes>(pet, "Attributes")
        .def(py::init<>())
        .def_readwrite("age", &Pet::Attributes::age);



    py::class_<Dog, Pet>(module, "Dog")
    .def(py::init<const std::string &>())
    .def("bark", &Dog::bark);

    // Return a base pointer to a derived instance
    module.def("pet_store", [](std::string name) { return std::unique_ptr<Pet>(new Dog(name)); });


    // Same binding code
    py::class_<PolymorphicPet>(module, "PolymorphicPet");
    py::class_<PolymorphicDog, PolymorphicPet>(module, "PolymorphicDog")
        .def(py::init<>())
        .def("bark", &PolymorphicDog::bark);

    // Again, return a base pointer to a derived instance
    module.def("pet_store2", []() { return std::unique_ptr<PolymorphicPet>(new PolymorphicDog); });
}



