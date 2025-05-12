#include <pybind11/pybind11.h>
#include <iostream>
#include <strstream>

#include "pybind_numpy.h"

namespace py = pybind11;

class Animal {
public:
    virtual std::string go(int n_times) = 0;
    virtual std::string name() { return "unknown"; }
};
class Dog : public Animal {
public:
    std::string go(int n_times) override {
        std::string result;
        for (int i=0; i<n_times; ++i)
            result += bark() + " ";
        return result;
    }
    virtual std::string bark() { return "woof!"; }
};


class Husky : public Dog {
public:
    Husky() {
        std::cout << "Husky init .." << std::endl;
    }
};


template <class AnimalBase = Animal> class PyAnimal : public AnimalBase {
public:
    using AnimalBase::AnimalBase; // Inherit constructors
    std::string go(int n_times) override { PYBIND11_OVERRIDE_PURE(std::string, AnimalBase, go, n_times); }
    std::string name() override { PYBIND11_OVERRIDE(std::string, AnimalBase, name, ); }
};


template <class DogBase = Dog> class PyDog : public PyAnimal<DogBase> {
public:
    using PyAnimal<DogBase>::PyAnimal; // Inherit constructors
    // Override PyAnimal's pure virtual go() with a non-pure one:
    PyDog() {
        std::cout << "PyDog init .." << std::endl;
    }

    std::string go(int n_times) override { PYBIND11_OVERRIDE(std::string, DogBase, go, n_times); }
    std::string bark() override { PYBIND11_OVERRIDE(std::string, DogBase, bark, ); }
};



std::string call_go(Animal *animal) {
    return animal->go(3);
}

class Example {
private:
    Example(int a) { this -> a = a;}; // private constructor
public:
    // Factory function - returned by value:
    static Example create(int a) { return Example(a); }

    // These constructors are publicly callable:
    Example(double c): c(c) {};
    Example(int a , int b): a(a), b(b) {};
    Example(std::string s): s(s) {};

    int a, b;
    double c;
    std::string s;

    std::string get_string() {
        std::strstream ss;
        ss << "a = " << a << " b = " << b << " c = " << c << " s = " << s << "\n";
        // ss << "error! value was " << actualValue << " but I expected " <<  expectedValue << endl;
        return ss.str();
    }

};


struct OwnsPythonObjects {
    py::object value = py::none();
};


class MyClass {
public:
    bool myMethod(int32_t & a);
};

bool MyClass::myMethod(int32_t& value)
{
    pybind11::gil_scoped_acquire gil;  // Acquire the GIL while in this scope.
    // Try to look up the overridden method on the Python side.
    pybind11::function override = pybind11::get_override(this, "myMethod");
    if (override) {  // method is found
        auto obj = override(value);  // Call the Python function.
        if (py::isinstance<py::int_>(obj)) {  // check if it returned a Python integer type
            value = obj.cast<int32_t>();  // Cast it and assign it to the value.
            return true;  // Return true; value should be used.
        } else {
            return false;  // Python returned none, return false.
        }
    }
    return false;  // Alternatively return MyClass::myMethod(value);
}


PYBIND11_MODULE(basic, m) {

    py::class_<Animal, PyAnimal<>> animal(m, "Animal");
    animal.def(py::init<>());
    animal.def("go", &Animal::go);

    py::class_<Dog, Animal, PyDog<>> dog(m, "Dog");
    dog.def(py::init_alias<>());
    dog.def("go", &Dog::go);

    py::class_<Husky, Dog, PyDog<Husky>> husky(m, "Husky");
    husky.def(py::init_alias<>());
    // ... add animal, dog, husky definitions

    // m.def("call_go", py::overload_cast<Animal *>(&call_go));
    m.def("call_go", &call_go);
    // m.def("call_go", py::overload_cast<Dog *>(&call_go));


    py::class_<Example>(m, "Example")
    // Bind the factory function as a constructor:
    .def(py::init(&Example::create))
    // Bind a lambda function returning a pointer wrapped in a holder:
    .def(py::init([](std::string arg) {
        return std::unique_ptr<Example>(new Example(arg));
    }))
    // Return a raw pointer:
    .def(py::init([](int a, int b) { return new Example(a, b); }))
    // You can mix the above with regular C++ constructor bindings as well:
    .def(py::init<double>())
    .def("__str__", &Example::get_string)
    ;


    py::class_<OwnsPythonObjects> cls(
    m, "OwnsPythonObjects", py::custom_type_setup([](PyHeapTypeObject *heap_type) {
        auto *type = &heap_type->ht_type;
        type->tp_flags |= Py_TPFLAGS_HAVE_GC;
        type->tp_traverse = [](PyObject *self_base, visitproc visit, void *arg) {
            auto &self = py::cast<OwnsPythonObjects&>(py::handle(self_base));
            Py_VISIT(self.value.ptr());
            return 0;
        };
        type->tp_clear = [](PyObject *self_base) {
            auto &self = py::cast<OwnsPythonObjects&>(py::handle(self_base));
            self.value = py::none();
            return 0;
        };

        type->tp_str = [](PyObject *self_base) {
            auto &self = py::cast<OwnsPythonObjects&>(py::handle(self_base));
            pybind11::print("add debug  info...");
            auto v = py::str(self.value);
            v.inc_ref();
            return v.ptr();
            // return &py::cast<py::object>(py::str("ok"));

        };
    }));
    cls.def(py::init<>());
    cls.def_readwrite("value", &OwnsPythonObjects::value);

    py::class_<MyClass>(m, "MyClass")
    .def(py::init())
    .def("myMethod", &MyClass::myMethod);

    InitNumpyBinding(m);
}




