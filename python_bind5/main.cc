#include <Python.h>
#include <iostream>

// #include "lib/Stu.h"
#include "lib/demo_type.h"

static PyObject* sub_hello(PyObject* self, PyObject* args) {
    // 打印类型名
    PySys_WriteStdout("self type: %s\n", Py_TYPE(self)->tp_name);

    // 打印 repr(self)
    PyObject* repr = PyObject_Repr(self);
    if (repr) {
        PySys_WriteStdout("self = %s\n", PyUnicode_AsUTF8(repr));
        Py_DECREF(repr);
    } else {
        PySys_WriteStderr("Failed to get repr(self)\n");
        PyErr_Clear();  // 防止异常干扰
    }

    // 如果是模块，打印模块名
    if (PyModule_Check(self)) {
        PyObject* name = PyObject_GetAttrString(self, "__name__");
        if (name) {
            PySys_WriteStdout("module name = %s\n", PyUnicode_AsUTF8(name));
            Py_DECREF(name);
        }
    }
    Py_RETURN_NONE;
}

static PyMethodDef SubMethods[] = {
    {"hello", sub_hello, METH_NOARGS, "Print hello from C++ submodule"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef submodule_def = {
    PyModuleDef_HEAD_INIT,
    "demo.submodule",  // 全限定名
    "C++ implemented submodule",
    -1,
    SubMethods,
};

int main(int argc, char** argv) {
    Py_Initialize();
    if (!Py_IsInitialized()) {
        std::cerr << "Failed to initialize Python" << std::endl;
        return 1;
    }

    PyObject* m;


    m = PyModule_Create(&submodule_def);
    if (m == NULL)
        return -1;

    // 2. 创建父模块 demo
    PyObject* demo_mod = PyModule_New("demo");
    if (!demo_mod) {
        std::cerr << "Failed to create parent module" << std::endl;
        return 1;
    }
    // 4. 把父模块注册到 sys.modules
    PyObject* sys_modules = PyImport_GetModuleDict();
    PyDict_SetItemString(sys_modules, "demo", demo_mod);

    PyObject* sub_m;
    if (!((sub_m = PyInit_demo(demo_mod)))) {
        PySys_WriteStderr("Failed to get PyInit_demo\n");

    }


    PyDict_SetItemString(sys_modules, "demo.sub_m", sub_m);


    std::cout << "Python initialized" << std::endl;
    PyRun_SimpleString("print('Hello from embedded Python with Bazel module mode!')");
    PyRun_SimpleString("import sys; print('Python version:', sys.version)");
    PyRun_SimpleString("import os; print('os __file__:', os.__file__)");
    PyRun_SimpleString("import demo; print('demo __name__:', demo.__name__)");
    PyRun_SimpleString("import demo.sub_m; print('demo.sub_m __name__:', demo.sub_m.__name__)");
    Py_Finalize();
    return 0;
}
