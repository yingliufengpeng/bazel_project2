
#include "demo_type.h"
#include <structmember.h>  // 必须包含这个头文件，否则 PyMemberDef 未定义

#include <iostream>
#include <ostream>

/* 定义一个简单对象结构 */
typedef struct {
    PyObject_HEAD
    int value;  // 一个简单属性
    double scale;
    PyObject* name;
} DemoObject;

// 迭代器结构
typedef struct {
    PyObject_HEAD
    int current;
    int stop;
} DemoIter;



extern PyTypeObject DemoType;  // ✅ 声明，不定义


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

static PyObject* Demo_str(PyObject* self) {

    if (!PyObject_TypeCheck(self, &DemoType)) {
        PyErr_SetString(PyExc_TypeError, "Expected a Demo object");
        return NULL;
    }
    DemoObject* r = (DemoObject*) self;
    // safe to use self->value
    return PyUnicode_FromFormat("%d", r->value);

}



// tp_iternext
static PyObject* DemoIter_iternext(DemoIter* self) {
    if (self->current >= self->stop) {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }
    PyObject* result = PyLong_FromLong(self->current);
    self->current += 1;
    return result;
}



PyTypeObject DemoIterType = {
    PyVarObject_HEAD_INIT(nullptr, 0)

    "demo.DemoIter",               // tp_name
    sizeof(DemoIter),              // tp_basicsize
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
    "DemoIter object",                   // tp_doc
    0,                               // tp_traverse
    0,                               // tp_clear
    0,                               // tp_richcompare
    0,                               // tp_weaklistoffset
    (getiterfunc) PyObject_SelfIter,                               // tp_iter
    (iternextfunc) DemoIter_iternext,                               // tp_iternext
    0,                    // tp_methods
    0,                               // tp_members
    0,                     // tp_getset
    0,                               // tp_base
    0,                               // tp_dict
    0,                               // tp_descr_get
    0,                               // tp_descr_set
    0,                               // tp_dictoffset
    0,                               // tp_init
    0,                               // tp_alloc
    PyType_GenericNew                // tp_new
};

/* 属性表 */
static PyGetSetDef Demo_getset[] = {
    {"value", (getter)demo_get_value, (setter)demo_set_value, "value property", NULL},
    {NULL} /* Sentinel */
};

// tp_iter: 创建一个 DemoIter 对象，并初始化
static PyObject* Demo_iter(DemoObject* self) {
    DemoIter* iter = PyObject_New(DemoIter, &DemoIterType);
    if (!iter) return NULL;

    iter->current = 0;
    iter->stop = self->value;
    return (PyObject*) iter;
}
static PyMemberDef Demo_members[] = {
    {"value", T_INT, offsetof(DemoObject, value), 0, "the numeric value"},
    {"scale", T_DOUBLE, offsetof(DemoObject, scale), 0, "scaling factor"},
    {"name",  T_OBJECT_EX, offsetof(DemoObject, name), 0, "name (str)"},
    {NULL}  // 哨兵，必须以 NULL 结尾
};
static void Demo_dealloc(DemoObject* self) {
    PySys_FormatStdout("Demo dealloc ...");
    Py_XDECREF(self->name);  // 释放引用
    Py_TYPE(self)->tp_free((PyObject*)self);  // 调用默认析构逻辑
}


PyTypeObject DemoType = {
    PyVarObject_HEAD_INIT(nullptr, 0)

    "Demo_A2",               // tp_name
    sizeof(DemoObject),              // tp_basicsize
    0,                               // tp_itemsize
    (destructor) Demo_dealloc,                               // tp_dealloc
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
    &Demo_str,                               // tp_str
    0,                               // tp_getattro
    0,                               // tp_setattro
    0,                               // tp_as_buffer
    Py_TPFLAGS_DEFAULT,              // tp_flags
    "Demo object",                   // tp_doc
    0,                               // tp_traverse
    0,                               // tp_clear
    0,                               // tp_richcompare
    0,                               // tp_weaklistoffset
    (getiterfunc) Demo_iter,                               // tp_iter
    0,                               // tp_iternext
    Demo_methods,                    // tp_methods
    Demo_members,                               // tp_members
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
    "basic.sub_m",  // 全限定名
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

    if (PyType_Ready(&DemoIterType) < 0)
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
    if (PyModule_AddObject(m, "Demo_Iter", (PyObject *)&DemoIterType) < 0) {
        Py_DECREF(&DemoType);
        Py_DECREF(m);
        return NULL;
    }

    std::cout << "自定义的模块的初始化成功..." << std::endl;

    return m;
}

