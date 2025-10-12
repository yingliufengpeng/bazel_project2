
#include "demo_type.h"

#include <iostream>
#include <ostream>

/* 定义一个简单对象结构 */
typedef struct {
    PyObject_HEAD
    int value;  // 一个简单属性
} DemoObject;

/* 方法示例 */
static PyObject* demo_increment(DemoObject* self, PyObject* args) {
    self->value += 1;
    return PyLong_FromLong(self->value);
}

/* 方法表 */
static PyMethodDef Demo_methods[] = {
    {"increment", (PyCFunction)demo_increment, METH_NOARGS, "Increment value by 1"},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

/* getter 示例 */
static PyObject* demo_get_value(DemoObject* self, void* closure) {
    return PyLong_FromLong(self->value);
}

/* setter 示例 */
static int demo_set_value(DemoObject* self, PyObject* value, void* closure) {
    long v = PyLong_AsLong(value);
    if (PyErr_Occurred()) return -1;
    self->value = (int)v;
    return 0;
}

/* 属性表 */
static PyGetSetDef Demo_getset[] = {
    {"value", (getter)demo_get_value, (setter)demo_set_value, "value property", NULL},
    {NULL} /* Sentinel */
};

static PyTypeObject DemoType = {
    PyVarObject_HEAD_INIT(nullptr, 0)

    "Demo_A2",               // tp_name
    sizeof(DemoObject),              // tp_basicsize
    0,                               // tp_itemsize
    0,                               // tp_dealloc
    0,                               // tp_vectorcall_offset
    0,                               // tp_getattr
    0,                               // tp_setattr
    0,                               // tp_as_async
    0,                               // tp_repr
    0,                               // tp_as_number
    0,                               // tp_as_sequence
    0,                               // tp_as_mapping
    0,                               // tp_hash
    0,                               // tp_call
    0,                               // tp_str
    0,                               // tp_getattro
    0,                               // tp_setattro
    0,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,              // tp_flags
    "Demo object",                   // tp_doc
    0,                               // tp_traverse
    0,                               // tp_clear
    0,                               // tp_richcompare
    0,                               // tp_weaklistoffset
    0,                               // tp_iter
    0,                               // tp_iternext
    Demo_methods,                    // tp_methods
    0,                               // tp_members
    Demo_getset,                     // tp_getset
    0,                               // tp_base
    0,                               // tp_dict
    0,                               // tp_descr_get
    0,                               // tp_descr_set
    0,                               // tp_dictoffset
    0,                               // tp_init
    0,                               // tp_alloc
    PyType_GenericNew                // tp_new
};



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







PyMODINIT_FUNC PyInit_demo(PyObject* m) {
    PyObject* sub_m;


    sub_m = PyModule_Create(&submodule_def);
    if (sub_m == NULL)
        return NULL;

    if (PyType_Ready(&DemoType) < 0)
        return NULL;

    std::cout << "自定义的模块的初始化..." << std::endl;

    Py_INCREF(&DemoType);
    if (PyModule_AddObject(m, "sub_m",  sub_m)) {
        Py_DECREF(&sub_m);
        return NULL;
    }

    if (PyModule_AddObject(m, "Demo_A2", (PyObject *)&DemoType) < 0) {
        Py_DECREF(&DemoType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

