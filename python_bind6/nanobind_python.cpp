#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include <iostream>
#include <functional>
#include  <memory>

#include "lib/demo_type.h"
#include "tools.h"


namespace nb = nanobind;
// -------------------------
// 全局回调对象
// -------------------------
std::shared_ptr<nb::object> global_callback;

void set_callback(nb::object cb) {
    global_callback = std::make_shared<nb::object>(cb);
}

void trigger_callback(int x) {
    if (global_callback) {
        nb::gil_scoped_acquire gil;  // 确保持有 GIL
        (*global_callback)(x);
    }
}

void clear_callback() {
    global_callback = nullptr;  // 手动释放引用
}




NB_MODULE(basic, m) {
    PyInit_demo(m.ptr());

    m.def("hello", [](const std::string& s) -> std::string { return "basic module ready"; });
    m.def("set_callback", &set_callback, "Register a Python callback");
    m.def("trigger_callback", &trigger_callback, "Call the registered callback");
    m.def("clear_callback", &clear_callback);  // <--- 新增
    m.def("import_and_call_with_args", &import_and_call_with_args,
      "Import a Python module and call a function with arguments");

}



