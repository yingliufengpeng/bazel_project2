#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include <iostream>
#include <functional>
#include  <memory>

#include "lib/demo_type.h"


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
void init(PyObject* m) {
    PyInit_demo(m);
}


void import_and_call_with_args(const std::string &module_name,
                               const std::string &func_name,
                               int arg1,
                               const std::string &arg2) {
    nb::gil_scoped_acquire gil;  // 获取 GIL

    // 导入模块
    PyObject* py_module = PyImport_ImportModule(module_name.c_str());
    if (!py_module) {
        PyErr_Print();
        throw std::runtime_error("Failed to import module: " + module_name);
    }

    // 获取函数对象
    PyObject* py_func = PyObject_GetAttrString(py_module, func_name.c_str());
    if (!py_func || !PyCallable_Check(py_func)) {
        PyErr_Print();
        Py_XDECREF(py_func);
        Py_DECREF(py_module);
        throw std::runtime_error("Function not found or not callable: " + func_name);
    }

    // 构造参数元组
    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, PyLong_FromLong(arg1));           // 注意 PyTuple_SetItem 会偷走引用
    PyTuple_SetItem(args, 1, PyUnicode_FromString(arg2.c_str()));

    // 调用函数
    PyObject* result = PyObject_CallObject(py_func, args);
    Py_DECREF(args);  // 元组引用计数递减

    if (!result) {
        PyErr_Print();
        Py_DECREF(py_func);
        Py_DECREF(py_module);
        throw std::runtime_error("Function call failed");
    }

    // 打印返回值（如果是字符串）
    if (PyUnicode_Check(result)) {
        std::cout << "Result: " << PyUnicode_AsUTF8(result) << std::endl;
    }

    Py_DECREF(result);
    Py_DECREF(py_func);
    Py_DECREF(py_module);
}



NB_MODULE(basic, m) {
    init(m.ptr());

    m.def("hello", [](const std::string& s) -> std::string { return "basic module ready"; });
    m.def("set_callback", &set_callback, "Register a Python callback");
    m.def("trigger_callback", &trigger_callback, "Call the registered callback");
    m.def("clear_callback", &clear_callback);  // <--- 新增
    m.def("import_and_call_with_args", &import_and_call_with_args,
      "Import a Python module and call a function with arguments");

}



