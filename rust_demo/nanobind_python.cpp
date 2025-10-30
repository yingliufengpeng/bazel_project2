#include <cstring>
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string.h>

#include <iostream>
#include <functional>
#include  <memory>

#include "cpp_lib/lib.h"

namespace nb = nanobind;

auto deleter = [](CppPerson* p) {
    if (!p) return;
    if (p -> person->name) free((void*) p -> person->name);
    delete p;                    // 释放 Person 对象
};


NB_MODULE(basic, m) {
    nb::class_<Person>(m, "Person")
        .def("get_name", [](Person* p){ return std::string(p->name); })
        .def("set_name", [](Person* p, const std::string& s){
            if (p->name) free((void*)p->name);
            p->name = strdup(s.c_str());
        })
        .def_rw("age", &Person::age);

    // 返回裸指针并使用 rv_policy::take_ownership，让 Nanobind delete 对象
    m.def("make_person", []() -> Person* {
        Person* p = make_person_ptr();  // 分配 Person，内部 name 已初始化
        return p;
    }, nb::rv_policy::take_ownership);



    m.def("process_img", [](const std::string &path) -> std::string {
        const char* res = process_img(path.c_str());
        std::string out(res);
        rust_free_string(res); // ✅ 释放 Rust 分配的字符串
        return out;
    });
}



