//
// Created by peng on 5/12/25.
//

#include "pybind_numpy.h"

#include <iostream>

#include "pybind11/numpy.h"
using namespace pybind11::literals; // to bring in the `_a` literal

namespace py = pybind11;

struct A {
    int x;
    double y;
};

struct B {
    int z;
    A a;
};

template <typename T>
void f(py::array_t<T> array) {
    for (auto e: array) {
        std::cout << 40 << std::endl;
    }
}

float my_func(int a, float b , double c) {
    return a * (b + 2 * c);
}

// 定义一个简单的 C++ 结构体
struct Point {
    float x;
    float y;
};

void test_py_demo() {

    py::print("hello world begin ...");

    py::print(1, 2.9, "three", "sep"_a="-");

    auto args = py::make_tuple("unpacked", true);
    py::print("->", *args, "end"_a="<-"); // -> unpacked True <-
    py::print("hello world end ...");

}


void InitNumpyBinding(pybind11::module& m) {

    py::class_<A>(m, "A")
    .def(py::init<int, double>());

    py::class_<B>(m, "B")
    .def(py::init<int, A>());


    m.def("test_py_demo", &test_py_demo);



    PYBIND11_NUMPY_DTYPE(A, x, y);
    PYBIND11_NUMPY_DTYPE(B, z, a);
    PYBIND11_NUMPY_DTYPE(Point, x, y);

    // m.def("f", &f<A>);
    // m.def("f", &f<B>);

    m.def("vectorized_func", py::vectorize(my_func));

    // 绑定一个函数，返回 Point 类型的 numpy 数组
    m.def("create_points", []() {
        // 创建一个包含 3 个 Point 的数组
        std::vector<Point> points = {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}};

        // 使用 py::array_t 创建 numpy 数组
        py::array_t<Point> arr(points.size());
        std::memcpy(arr.mutable_data(), points.data(), points.size() * sizeof(Point));
        return arr;
    });

    // 绑定一个函数，接受并处理 Point 类型的 numpy 数组
    m.def("print_points", [](py::array_t<Point> arr) {
        // 获取数组的只读视图
        auto r = arr.unchecked<1>(); // 1 表示一维数组
        for (ssize_t i = 0; i < r.shape(0); ++i) {
            std::cout << "Point " << i << ": x=" << r(i).x << ", y=" << r(i).y << std::endl;
        }
    });


    m.def("utf8_test",
    [](const std::string &s) {
        std::cout << "utf-8 is icing on the cake.\n";
        std::cout << s;
    }
);
    m.def("utf8_charptr",
        [](const char *s) {
            std::cout << "My favorite food is\n";
            std::cout << s;
        }
    );

    m.def("return_bytes",
        []() {
            std::string s("\xba\xd0\xba\xd0");  // Not valid UTF-8
            return py::bytes(s);  // Return the data without transcoding
        }
    );
}
