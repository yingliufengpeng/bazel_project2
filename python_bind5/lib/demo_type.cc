
#include "demo_type.h"
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



/* 模块初始化 */
static PyModuleDef demomodule = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "zzz.peng",
    .m_doc = "Demo module with custom type",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_libpeng_demo(void) {
    PyObject* m;
    if (PyType_Ready(&DemoType) < 0)
        return NULL;

    m = PyModule_Create(&demomodule);
    if (!m)
        return NULL;

    Py_INCREF(&DemoType);
    if (PyModule_AddObject(m, "DemoObject", (PyObject *)&DemoType) < 0) {
        Py_DECREF(&DemoType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
