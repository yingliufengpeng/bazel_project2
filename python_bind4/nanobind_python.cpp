#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
// #include <nanobind/stl/vector.h>
#include <nanobind/make_iterator.h> // Include for make_iterator


#include <iostream>
#include <vector>

#include "basic.h"
#include "Pet.h"
#include "Dog.h"
#include "PolymorphhicPet.h"


namespace nb = nanobind;

struct Data {
    int value;
    Data(int v) : value(v) {}
};

class Container {
    Data* data;
public:
    Container(Data* d) : data(d) {}
    Data* get_data() { return data; }
};

static Data static_data(42); // 静态对象

void print_dict(const nb::dict& dict, nb::args args, nb::kwargs kwargs) {
    for (auto item : dict) {
    }
        // nb::print("key= ", item.first, " value = ", item.second);

    for (auto item: args) {
        //nb::print("key= ", item);

    }

    for (auto item : kwargs) {
    }
        //nb::print("key= ", item.first, " value = ", item.second);

}


NB_MODULE(basic, module) {
    module.doc() = "A basic pybind11 extension";
    module.def("add", &add, "A function that adds two numbers");
    module.attr("the_answer") = 42;
    nb::object world = nb::cast("World");
    module.attr("world") = world;


    module.def("print_dict", &print_dict);

    nb::class_<Data>(module, "Data")
    .def_rw("value", &Data::value);

    nb::class_<Container>(module, "Container")
    .def(nb::init<Data*>())
    .def("get_data", &Container::get_data, nb::rv_policy::reference);


    module.def("get_static_data", []() { return &static_data; }, nb::rv_policy::reference);
    // module.def("get_static_data", []() { return &static_data; }   );


    auto pet = nb::class_<Pet>(module, "Pet", nb::dynamic_attr())
      .def(nb::init<const std::string& >())
      .def(nb::init<const std::string &, Pet::Kind>())
      .def("setName", &Pet::setName)
      .def("getName", &Pet::getName)
      .def("show", &Pet::show)
      .def_rw("type", &Pet::type)
      .def_rw("attr", &Pet::attr)
      .def("__repr__", [](const Pet &a) {
          return "Pet {" + a.getName() + "}";
      })

    .def("set", nb::overload_cast<int>(&Pet::set), "Set the pet's age")
    .def("set", nb::overload_cast<const std::string &>(&Pet::set), "Set the pet's name")
    .def_rw("name", &Pet::name);

    nb::enum_<Pet::Kind>(pet, "Kind")
    .value("Dog", Pet::Kind::Dog)
    .value("Cat", Pet::Kind::Cat)
    .export_values();

    nb::class_<Pet::Attributes>(pet, "Attributes")
        .def(nb::init<>())
        .def_rw("age", &Pet::Attributes::age);



    nb::class_<Dog, Pet>(module, "Dog")
    .def(nb::init<const std::string &>())
    .def("bark", &Dog::bark);

    // Return a base pointer to a derived instance
    // module.def("pet_store", [](std::string name) { return std::unique_ptr<Pet>(new Dog(name)); });
    module.def("pet_store", [](std::string name) { return (Pet *) new Dog(name); }  );

    // Same binding code
    nb::class_<PolymorphicPet>(module, "PolymorphicPet");
    nb::class_<PolymorphicDog, PolymorphicPet>(module, "PolymorphicDog")
        .def("bark", &PolymorphicDog::bark);

    // Again, return a base pointer to a derived instance
    module.def("pet_store2", []() { return   (PolymorphicPet *) new PolymorphicDog(); });


     nb::class_<std::vector<int>>(module, "IntVector")
    .def(nb::init<>())
    .def("clear", &std::vector<int>::clear)
    .def("pop_back", &std::vector<int>::pop_back)
    .def("__len__", [](const std::vector<int> &v) { return v.size(); })
    .def("__iter__", [](std::vector<int> &v) {
        return nb::make_iterator(nb::type<std::vector<int>>(),"iter", v.begin(), v.end());
    }, nb::keep_alive<0, 1>())   // 关键：保证 v 活着时迭代器活着
    .def("push_back", [](std::vector<int> &v, int value) {
        v.push_back(value);
    });
}



